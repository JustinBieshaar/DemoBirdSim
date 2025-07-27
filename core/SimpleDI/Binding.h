#pragma once
#include <functional>
#include <memory>

#include "Lifetime.h"

namespace SimpleDI
{
    struct Binding
    {
        Lifetime lifetime;
        /// <summary>
        /// factory is used to define the creation of the type. So when this type is being resolved it's using it's factory for creation.
        /// </summary>
        std::function<std::shared_ptr<void>()> factory;

        /// <summary>
        /// Cached instance is used for singleton use case to ensure there's only one by caching it.
        /// If there's no cached instance, we'll generate one.
        /// </summary>
        std::shared_ptr<void> cachedInstance;
    };
}