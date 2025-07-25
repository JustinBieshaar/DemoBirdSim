#pragma once
#include <typeindex>

namespace Signals
{
    /// <summary>
    /// This handle is used as a unique key for caching what's registered as observer.
    /// This key can then be used to remove the observation.
    /// </summary>
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