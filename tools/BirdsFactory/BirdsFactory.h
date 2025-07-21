// BirdFactory.h
#pragma once
#include <json.hpp>

class BirdsFactory
{
public:
    static void generateBirds(nlohmann::json& birdsJson);

private:
    static std::string toMacro(const std::string& name);

    static void generateBirdInterface(nlohmann::json& json);
    static void generateBirdClass(const std::string& name, nlohmann::json& json);
    static void generateDefines(nlohmann::json& birds);
    static void generateRegisterIncludes(nlohmann::json& birds);
    static void generateRegistryAccessors(nlohmann::json& birds);
    static void runPremake();
};