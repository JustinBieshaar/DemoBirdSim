#pragma once
#include <json.hpp>

struct JsonUpdatedSignal
{
	nlohmann::ordered_json json;
};