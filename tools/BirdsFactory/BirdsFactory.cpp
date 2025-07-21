#include "BirdsFactory.h"
#include <fstream>
#include <filesystem>
#include <cctype>
#include <iostream>
#include <StringUtils.h>

using json = nlohmann::json;

const std::filesystem::path BASE_DIR = std::filesystem::path(__FILE__).parent_path();

/*
* Just a little heads up. What you are about to see in this factory is some code generation.
* This may be overwhelming to look at. But it's working completely fine. ;P
*/

void BirdsFactory::generateBirds(const json& birds)
{
    std::filesystem::remove_all(BASE_DIR / "Birds");
    std::filesystem::create_directory(BASE_DIR / "Birds");

    for (auto& [name, data] : birds.items())
    {
        std::string obj = data["obj_name"];
        auto core = data["core"];
        auto flight = data["flight"];
        generateBirdClass(name, obj, core, flight);
    }

    generateDefines(birds);
    generateRegisterIncludes(birds);
    generateRegistryAccessors(birds);
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

void BirdsFactory::generateBirdClass(const std::string& name, const std::string& obj, nlohmann::json& core, nlohmann::json& flight)
{
    std::string className = StringUtils::toPascalCase(name);
    std::filesystem::path filePath = BASE_DIR / "Birds" / (className + ".h");

    std::ofstream file(filePath);
    file << "#pragma once\n"
        << "#include \"../IBird.h\"\n\n"
        << "class " << className << " : public IBird {\n"
        << "public:\n"
        << "    " << className << "() {}\n"
        << "    std::string getObjName() const override { return \"" << obj << "\"; }\n"
        << "    int getAcceleration() const override { return " << flight["acceleration"] << "; }\n"
        << "    std::string getName() const override { return \"" << name << "\"; }\n"
        << "};";
}

void BirdsFactory::generateDefines(const json& birds)
{
    std::ofstream defines((BASE_DIR / "BirdDefines.h").string());
    defines << "#pragma once\n\n";
    for (auto& [name, _] : birds.items())
    {
        defines << "#define " << toMacro(name) << " \"" << name << "\"\n";
    }
}

void BirdsFactory::generateRegisterIncludes(const json& birds)
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
        << "{\n";

    for (auto& [name, _] : birds.items())
    {
        reg << "    static std::shared_ptr<" << StringUtils::toPascalCase(name) << "> get_" << StringUtils::toUpperSnakeCase(name) << "()\n"
            << "    {\n"
            << "        ensureInitialized();\n\n"
            << "        auto it = m_list.find(\"" << name << "\");\n"
            << "        if (it != m_list.end()) return std::dynamic_pointer_cast<" << StringUtils::toPascalCase(name) << ">(it->second);\n"
            << "        return nullptr;\n"
            << "    }\n\n";
    }

    reg << "    static std::shared_ptr<IBird> getInstance(const std::string& name)\n"
        << "    {\n"
        << "        ensureInitialized();\n\n"

        << "        auto it = m_list.find(name);\n"
        << "        if (it != m_list.end()) return it->second;\n"
        << "        return nullptr;\n"
        << "    }\n";

    reg << "private:\n";


    reg << "    static void ensureInitialized()\n"
        << "    {\n"
        << "        if(m_isInitialized) return;\n";

    for (auto& [name, _] : birds.items())
    {
        reg << "        m_list[\"" << name << "\"] = std::make_shared<" << StringUtils::toPascalCase(name) << ">();\n";
    }

    reg << "\n"
        << "        m_isInitialized = true;\n"
        << "    };\n\n";


    reg << "    static inline bool m_isInitialized = false;\n"
        << "    static std::unordered_map<std::string, std::shared_ptr<IBird>> m_list;\n";

    reg << "};";
}

void BirdsFactory::generateRegistryAccessors(const json& birds)
{
    std::ofstream reg("BirdsRegistry.h");
    reg << "#pragma once\n";
    reg << "#include \"BirdFactory.h\"\n";
    reg << "#include \"BirdDefines.h\"\n\n";
    reg << "namespace BirdsRegistry {\n";

    for (auto& [name, _] : birds.items())
    {
        std::string className = StringUtils::toPascalCase(name);
        std::string macro = toMacro(name);
        reg << "    inline std::shared_ptr<Bird> " << className << "() {\n";
        reg << "        return BirdFactory::getInstance().getBird(" << macro << ");\n";
        reg << "    }\n";
    }

    reg << "}\n";
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
