#pragma once

#include <functional>
#include <memory>
#include <unordered_map>
#include <typeindex>
#include <stdexcept>

#include "Lifetime.h"

/// <summary>
/// A minimal dependency injection container.
/// </summary>
class DIContainer
{
public:
    template <typename Interface, typename Impl, typename... Args>
    void bind(DI::Lifetime lifetime, Args&&... args)
    {
        Binding binding;
        binding.lifetime = lifetime;

        if (lifetime == DI::Lifetime::Singleton)
        {
            // Factory that caches instance inside Binding
            binding.factory = [binding, ... args = std::forward<Args>(args)]() mutable -> std::shared_ptr<void>
                {
                    if (!binding.cachedInstance)
                    {
                        binding.cachedInstance = std::make_shared<Impl>(args...);
                    }
                    return binding.cachedInstance;
                };
        }
        else if (lifetime == DI::Lifetime::Transient)
        {
            // New instance each time
            binding.factory = [... args = std::forward<Args>(args)]() -> std::shared_ptr<void>
                {
                    return std::make_shared<Impl>(args...);
                };
        }

        m_bindings[typeid(Interface)] = std::move(binding);
    }

    template <typename Interface>
    void bindInstance(std::shared_ptr<Interface> instance)
    {
        Binding binding;
        binding.lifetime = DI::Lifetime::Instance;
        binding.cachedInstance = instance;
        binding.factory = [instance]() -> std::shared_ptr<void>
            {
                return instance;
            };

        m_bindings[typeid(Interface)] = std::move(binding);
    }

    template <typename Interface>
    std::shared_ptr<Interface> resolve()
    {
        auto it = m_bindings.find(typeid(Interface));
        if (it == m_bindings.end())
        {
            throw std::runtime_error("Type not bound!");
        }
        return std::static_pointer_cast<Interface>(it->second.factory());
    }

private:

    struct Binding
    {
        DI::Lifetime lifetime;
        std::function<std::shared_ptr<void>()> factory;
        std::shared_ptr<void> cachedInstance;
    };

    std::unordered_map<std::type_index, Binding> m_bindings;
};