#include <json.hpp>
#include <fstream>
#include <iostream>
#include <filesystem>
#include <sstream>
#include <cctype>
using json = nlohmann::json;

std::string toPascalCase(const std::string& name)
{
    std::string out = name;
    out[0] = std::toupper(out[0]);
    return out;
}

std::string toMacro(const std::string& name)
{
    std::string macro = "BIRD_";
    for (char c : name)
    {
        macro += std::toupper(c);
    }
    return macro;
}

void generateBirdClass(const std::string& name, const std::string& obj, int speed)
{
    std::string className = toPascalCase(name);
    std::string filePath = "Birds/" + className + ".h";

    std::ofstream file(filePath);
    file << "#pragma once\n"
        << "#include \"../Bird.h\"\n"
        << "#include \"../BirdFactory.h\"\n\n"
        << "class " << className << " : public Bird {\n"
        << "public:\n"
        << "    " << className << "() {}\n"
        << "    std::string getObjName() const override { return \"" << obj << "\"; }\n"
        << "    int getSpeed() const override { return " << speed << "; }\n"
        << "    std::string getName() const override { return \"" << name << "\"; }\n"
        << "private:\n"
        << "    static bool registered;\n"
        << "};\n\n"
        << "bool " << className << "::registered = [](){\n"
        << "    BirdFactory::getInstance().registerBird(\"" << name << "\", []() {\n"
        << "        return std::make_shared<" << className << ">();\n"
        << "    });\n"
        << "    return true;\n"
        << "}();\n";
}

void generateDefines(const json& birds)
{
    std::ofstream defines("BirdDefines.h");
    defines << "#pragma once\n\n";
    for (auto& [name, _] : birds.items())
    {
        defines << "#define " << toMacro(name) << " \"" << name << "\"\n";
    }
}

void generateRegisterIncludes(const json& birds)
{
    std::ofstream reg("BirdRegister.cpp");
    reg << "// Auto-generated: includes all birds\n";
    for (auto& [name, _] : birds.items())
    {
        reg << "#include \"Birds/" << toPascalCase(name) << ".h\"\n";
    }
}

int main()
{
    std::ifstream input("birds.json");
    if (!input)
    {
        std::cerr << "birds.json not found\n";
        return 1;
    }

    json birds;
    input >> birds;

    std::filesystem::remove_all("Birds");
    std::filesystem::create_directory("Birds");

    for (auto& [name, data] : birds.items())
    {
        std::string obj = data["obj_name"];
        int speed = data["speed"];
        generateBirdClass(name, obj, speed);
    }

    generateDefines(birds);
    generateRegisterIncludes(birds);

    std::cout << "Birds generated.\n";
    return 0;
}