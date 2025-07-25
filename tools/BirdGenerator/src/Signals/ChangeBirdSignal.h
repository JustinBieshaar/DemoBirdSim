#pragma once
#include <string>
#include <json.hpp>

/// <summary>
/// Signal a different bird is selected
/// </summary>
struct ChangeBirdSignal
{
	std::string name;
	nlohmann::ordered_json birdJson;
};