/*
* Just a little heads up. What you are about to see in this factory is some code generation.
*/

#include "BirdsFactory.h"

#include <fstream>
#include <filesystem>
#include <cctype>
#include <iostream>

#include <StringUtils.h>
#include "JsonUtils.h"

// defining the path of the generation directory
const std::filesystem::path BASE_DIR = std::filesystem::path(__FILE__).parent_path();

void BirdsFactory::generateBirds(nlohmann::ordered_json& birds)
{
    std::filesystem::remove_all(BASE_DIR / "Birds");
    std::filesystem::create_directory(BASE_DIR / "Birds");

    // getting first entry just to fill the bird interface as it will just generate getters for all fields.
    // as we ensure each entry is sharing the same template, there's no risk in using the first entry as it's
    // just a reference. Potentially could also have used the template input here, but it's not a necessity.
    auto it = birds.begin();
    std::string currentKey = it.key();
    nlohmann::ordered_json& firstEntry = it.value();

    generateBirdInterface(firstEntry);

    for (auto& [name, data] : birds.items())
    {
        generateBirdClass(name, data);
    }

    generateDefines(birds);
    generateRegisterIncludes(birds);
    std::cout << "Birds generated.\n";
    runPremake();
}

std::string BirdsFactory::toMacro(const std::string& name)
{
    std::string macro = "BIRD_";
    for (char c : name)
    {
        macro += std::toupper(c);
    }
    return macro;
}

void BirdsFactory::generateBirdInterface(nlohmann::ordered_json& json)
{
    std::string className = "IBird";
    std::filesystem::path filePath = BASE_DIR / (className + ".h");

    std::ofstream file(filePath);
    file << "// Auto-generated: Base interface of all birds.\n"
        << "// DO NOT ADJUST MANUALLY!\n\n"

        << "#pragma once\n"
        << "#include <string>\n\n"
        << "class " << className << "\n"
        << "{\n"
        << "public:\n"
        << "    " << className << "() {}\n"
        << "    virtual ~" << className << "() = default;\n\n" 
        
        << "    virtual std::string getName() const = 0;\n";

    for (auto& [key, value] : json.items())
    {
        // objects are only used to structure the bird generation view so they
        // act as foldable headers. Thereby we only render all the items of an object.
        // This has a flaw when there's another object inside an object. So this must be
        // refactored to a recursive solution if that needs to be supported.
        if (value.is_object())
        {
            for (auto& [key2, value2] : value.items())
            {
                file << "   virtual " << JsonUtils::getJsonFieldTypeToString(key2, value2) << " get" << StringUtils::toPascalCase(key2) << "() const = 0;\n";
            }
        }
        else
        {
            file << "   virtual " << JsonUtils::getJsonFieldTypeToString(key, value) << " get" << StringUtils::toPascalCase(key) << "() const = 0;\n";
        }
    }

    file << "};";
        
}

void BirdsFactory::generateBirdClass(const std::string& name, nlohmann::ordered_json& json)
{
    std::string className = StringUtils::toPascalCase(name);
    std::filesystem::path filePath = BASE_DIR / "Birds" / (className + ".h");

    std::ofstream file(filePath);
    file << "// Auto-generated: bird instance.\n"
        << "// DO NOT ADJUST MANUALLY!\n\n"

        << "#pragma once\n"
        << "#include \"../IBird.h\"\n\n"
        << "namespace Birds {\n"
        << "    class " << className << " : public IBird {\n"
        << "    public:\n"
        << "        " << className << "() {}\n"
        << "        ~" << className << "() {}\n\n";

    file << "       std::string getName() const override { return \"" << name << "\"; };\n\n";

    // all getters
    for (auto& [key, value] : json.items())
    {
        // objects are only used to structure the bird generation view so they
        // act as foldable headers. Thereby we only render all the items of an object.
        // This has a flaw when there's another object inside an object. So this must be
        // refactored to a recursive solution if that needs to be supported.
        if (value.is_object())
        {
            for (auto& [key2, value2] : value.items())
            {
                file << "       " << JsonUtils::getJsonFieldTypeToString(key2, value2) << " get" << StringUtils::toPascalCase(key2) << "() const override { return " << JsonUtils::getJsonFieldValueToString(value2) << "; }\n";
            }
        }
        else
        {
            file << "       " << JsonUtils::getJsonFieldTypeToString(key, value) << " get" << StringUtils::toPascalCase(key) << "() const override { return " << JsonUtils::getJsonFieldValueToString(value) << "; }\n";
        }
    }


    file << "   };\n"
        << "}";
}

void BirdsFactory::generateDefines(nlohmann::ordered_json& birds)
{
    std::ofstream defines((BASE_DIR / "BirdDefines.h").string());
    defines << "// Auto-generated: defines of all generated birds.\n"
        << "// DO NOT ADJUST MANUALLY!\n\n"

        << "#pragma once\n\n";

    // create defines
    for (auto& [name, _] : birds.items())
    {
        defines << "#define " << toMacro(name) << " \"" << name << "\"\n";
    }
}

void BirdsFactory::generateRegisterIncludes(nlohmann::ordered_json& birds)
{
    std::ofstream reg((BASE_DIR / "BirdRegistry.h").string());

    // includes
    reg << "// Auto-generated: includes all birds\n"
        << "// DO NOT ADJUST MANUALLY!\n\n"

        << "#include <unordered_map>\n"
        << "#include <memory>\n\n";

    reg << "#include \"IBird.h\"\n";

    // include all generated birds
    for (auto& [name, _] : birds.items())
    {
        reg << "#include \"Birds/" << StringUtils::toPascalCase(name) << ".h\"\n";
    }

    // base of class
    reg << "\n"
        << "class BirdRegistry\n"
        << "{\n"
        << "public:\n"
        << "    BirdRegistry() = delete;\n"
        << "    BirdRegistry(const BirdRegistry&) = delete;\n"
        << "    BirdRegistry& operator=(const BirdRegistry&) = delete;\n";

    reg << "    inline static const IBird* getInstance(const std::string& name)\n"
        << "    {\n"
        << "        ensureInitialized();\n\n"

        << "        auto it = m_list.find(name);\n"
        << "        if (it != m_list.end()) return it->second.get();\n"
        << "        return nullptr;\n"
        << "    }\n\n";

    reg << "    inline static std::vector<std::string> getAllEntries()\n"
        << "    {\n"
        << "        ensureInitialized();\n\n"
        << "        return m_entries;\n"
        << "    }\n\n";


    reg << "private:\n";


    reg << "    inline static void ensureInitialized()\n"
        << "    {\n"
        << "        if(m_isInitialized) return;\n";

    for (auto& [name, _] : birds.items())
    {
        reg << "        m_list[\"" << name << "\"] = std::make_shared<Birds::" << StringUtils::toPascalCase(name) << ">();\n";
        reg << "        m_entries.push_back(\"" << name << "\");\n";
    }

    reg << "\n"
        << "        m_isInitialized = true;\n"
        << "    };\n\n";


    reg << "    inline static inline bool m_isInitialized = false;\n"
        << "    inline static std::unordered_map<std::string, std::shared_ptr<IBird>> m_list;\n"
        << "    inline static std::vector<std::string> m_entries;\n";

    reg << "};";
}

void BirdsFactory::runPremake()
{
#ifdef _WIN32
    // Proceed only on Windows platforms
#else
    // Unsupported OS: friendly warning and early return
    std::cout << "This does only work in Windows.. Please ask Justin Scott Bieshaar to add your OS support. ;)\n";
    return;
#endif

    // Get the absolute path of this source file at compile time
    std::filesystem::path currentFile = std::filesystem::path(__FILE__);

    // Derive the directory containing this file (i.e., BirdsFactory/)
    std::filesystem::path currentDir = currentFile.parent_path();

    // Compute the solution root directory by going two levels up
    std::filesystem::path solutionDir = std::filesystem::absolute(currentDir / "../../");

    // Construct the full path to the premake script
    std::filesystem::path batPath = solutionDir / "premake-win.bat";

    // Check if the .bat file actually exists before trying to run it
    if (!std::filesystem::exists(batPath))
    {
        std::cerr << "ERROR: premake-win.bat not found at: " << batPath << "\n";
        return;
    }

    // Extract the directory containing the .bat file
    std::filesystem::path batDir = batPath.parent_path();

    // Compose the system command:
    // - Use `cmd /C` to execute a single command
    // - Change to the .bat directory with `cd /d`
    // - `echo.` is a trick to ensure the batch file gets called properly
    std::string command = "cmd /C \"cd /d \"" + batDir.string() + "\" && echo. | premake-win.bat\"";

    std::cout << "Running command: " << command << "\n";

    // Execute the command
    int result = std::system(command.c_str());

    // Check the result of the system call
    if (result != 0)
    {
        std::cerr << "Error running premake-win.bat. Exit code: " << result << "\n";
    }
    else
    {
        std::cout << "Premake executed successfully.\n";
    }
}
