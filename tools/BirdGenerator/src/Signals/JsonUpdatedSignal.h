#pragma once
#include <json.hpp>

/// <summary>
/// Signal the json is updated.
/// This to update views and such.
/// </summary>
struct JsonUpdatedSignal
{
	nlohmann::ordered_json json;
};