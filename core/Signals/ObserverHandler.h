#pragma once
#include <typeindex>

namespace Signals
{
    struct ObserverHandle
    {
        std::type_index type;
        size_t id;

        bool operator==(const ObserverHandle& other) const
        {
            return type == other.type && id == other.id;
        }
    };
}