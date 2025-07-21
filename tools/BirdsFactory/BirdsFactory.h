// BirdFactory.h
#pragma once
#include <json.hpp>

class BirdsFactory
{
public:
    static void generateBirds(nlohmann::ordered_json& birdsJson);

private:
    static std::string toMacro(const std::string& name);

    static void generateBirdInterface(nlohmann::ordered_json& json);
    static void generateBirdClass(const std::string& name, nlohmann::ordered_json& json);
    static void generateDefines(nlohmann::ordered_json& birds);
    static void generateRegisterIncludes(nlohmann::ordered_json& birds);
    static void generateRegistryAccessors(nlohmann::ordered_json& birds);
    static void runPremake();
};