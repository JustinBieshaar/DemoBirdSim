// BirdFactory.h
#pragma once
#include <json.hpp>

class BirdsFactory
{
public:
    /// <summary>
    /// Generates the following files;
    /// IBird (base interface of each bird)
    /// BirdsRegistry (registry with all birds instanced)
    /// BirdDefines (define of all bird names, could be used to fetch a specific bird)
    /// Birds/[All birds] (all birds with generated data from json)
    /// </summary>
    /// <param name="birds"></param>
    static void generateBirds(nlohmann::ordered_json& birdsJson);

private:
    /// <summary>
    /// returns a macro name using BIRD_ prefix. So if you generate bird: robin.
    /// A macro BIRD_ROBIN will be returned (used for defines)
    /// </summary>
    static std::string toMacro(const std::string& name);

    static void generateBirdInterface(nlohmann::ordered_json& json);
    static void generateBirdClass(const std::string& name, nlohmann::ordered_json& json);
    static void generateDefines(nlohmann::ordered_json& birds);
    static void generateRegisterIncludes(nlohmann::ordered_json& birds);

    /// <summary>
    /// Runs premake to ensure reloading the project when entering this solution to be able
    /// to inspect the generated files immediately.
    /// </summary>
    static void runPremake();
};