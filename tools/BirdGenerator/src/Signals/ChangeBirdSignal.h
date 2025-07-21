#pragma once
#include <string>
#include <json.hpp>

struct ChangeBirdSignal
{
	std::string name;
	nlohmann::ordered_json birdJson;
};