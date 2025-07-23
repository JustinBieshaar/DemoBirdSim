#include "BirdsFactory.h"
#include <fstream>
#include <filesystem>
#include <cctype>
#include <iostream>
#include <StringUtils.h>

#include "JsonUtils.h"

const std::filesystem::path BASE_DIR = std::filesystem::path(__FILE__).parent_path();

/*
* Just a little heads up. What you are about to see in this factory is some code generation.
* This may be overwhelming to look at. But it's working completely fine. ;P
*/

void BirdsFactory::generateBirds(nlohmann::ordered_json& birds)
{
    std::filesystem::remove_all(BASE_DIR / "Birds");
    std::filesystem::create_directory(BASE_DIR / "Birds");

    // getting first entry just to fill the bird interface as it will just generate getters for all fields.
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
    file << "#pragma once\n"
        << "#include <string>\n\n"
        << "class " << className << "\n"
        << "{\n"
        << "public:\n"
        << "    " << className << "() {}\n"
        << "    virtual ~" << className << "() = default;\n\n";

    file << "   virtual std::string getName() = 0;\n";

    for (auto& [key, value] : json.items())
    {
        // when value is an object it's designed to be a layer of values. We can ignore this layer
        // here and loop through all values.
        // todo, support multi layer
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
    file << "#pragma once\n"
        << "#include \"../IBird.h\"\n\n"
        << "class " << className << " : public IBird {\n"
        << "public:\n"
        << "    " << className << "() {}\n";

    file << "    std::string getName() { return \"" << name << "\"; };\n\n";

    for (auto& [key, value] : json.items())
    {

        if (value.is_object())
        {
            for (auto& [key2, value2] : value.items())
            {
                file << "    " << JsonUtils::getJsonFieldTypeToString(key2, value2) << " get" << StringUtils::toPascalCase(key2) << "() const override { return " << JsonUtils::getJsonFieldValueToString(value2) << "; }\n";
            }
        }
        else
        {
            file << "    " << JsonUtils::getJsonFieldTypeToString(key, value) << " get" << StringUtils::toPascalCase(key) << "() const override { return " << JsonUtils::getJsonFieldValueToString(value) << "; }\n";
        }
    }


    file << "};";
}

void BirdsFactory::generateDefines(nlohmann::ordered_json& birds)
{
    std::ofstream defines((BASE_DIR / "BirdDefines.h").string());
    defines << "#pragma once\n\n";
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
        << "public:\n";

    for (auto& [name, _] : birds.items())
    {
        reg << "    inline static std::shared_ptr<" << StringUtils::toPascalCase(name) << "> get" << StringUtils::toPascalCase(name) << "()\n"
            << "    {\n"
            << "        ensureInitialized();\n\n"
            << "        auto it = m_list.find(\"" << name << "\");\n"
            << "        if (it != m_list.end()) return std::dynamic_pointer_cast<" << StringUtils::toPascalCase(name) << ">(it->second);\n"
            << "        return nullptr;\n"
            << "    }\n\n";
    }

    reg << "    inline static std::shared_ptr<IBird> getInstance(const std::string& name)\n"
        << "    {\n"
        << "        ensureInitialized();\n\n"

        << "        auto it = m_list.find(name);\n"
        << "        if (it != m_list.end()) return it->second;\n"
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
        reg << "        m_list[\"" << name << "\"] = std::make_shared<" << StringUtils::toPascalCase(name) << ">();\n";
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
    // Windows (both 32-bit and 64-bit)
#else
    std::cout << "This does only work in windows.. Please ask Justin Scott Bieshaar to add your OS support. ;)\n";
    return;
#endif

    std::filesystem::path currentFile = std::filesystem::path(__FILE__);
    std::filesystem::path currentDir = currentFile.parent_path(); // BirdsFactory/
    std::filesystem::path solutionDir = std::filesystem::absolute(currentDir / "../../");
    std::filesystem::path batPath = solutionDir / "premake-win.bat";

    if (!std::filesystem::exists(batPath))
    {
        std::cerr << "ERROR: premake-win.bat not found at: " << batPath << "\n";
        return;
    }

    std::filesystem::path batDir = batPath.parent_path();

    // This command sets the working directory to the .bat location, then runs it
    std::string command = "cmd /C \"cd /d \"" + batDir.string() + "\" && echo. | premake-win.bat\"";

    std::cout << "Running command: " << command << "\n";

    int result = std::system(command.c_str());

    if (result != 0)
    {
        std::cerr << "Error running premake-win.bat. Exit code: " << result << "\n";
    }
    else
    {
        std::cout << "Premake executed successfully.\n";
    }
}
