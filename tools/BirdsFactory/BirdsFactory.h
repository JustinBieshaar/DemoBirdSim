// BirdFactory.h
#pragma once
#include <json.hpp>

class BirdsFactory
{
public:
    static void generateBirds(const nlohmann::json& birdsJson);

private:
    static std::string toMacro(const std::string& name);

    static void generateBirdClass(const std::string& name, const std::string& obj, int speed);
    static void generateDefines(const nlohmann::json& birds);
    static void generateRegisterIncludes(const nlohmann::json& birds);
    static void generateRegistryAccessors(const nlohmann::json& birds);
    static void runPremake();
};