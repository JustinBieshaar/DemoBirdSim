#pragma once

#include <functional>
#include <memory>
#include <unordered_map>
#include <typeindex>
#include <stdexcept>

#include "Lifetime.h"

/// <summary>
/// A minimal dependency injection container supporting Singleton, Transient, and pre-instantiated lifetimes.
/// I've been considering to dive in Boost DI, as I read some cool articles about it. However, as I once in my
/// life been rejected for using a 3rd party DI library in Unity3D. I since then decided to create my own simple
/// dependency injection systems to show my understanding of the pattern. ;)
/// </summary>
class DIContainer
{
public:
    /// <summary>
    /// Binds an interface to a concrete implementation type with optional constructor arguments.
    /// </summary>
    /// <param name="lifetime">Lifetime of the created instance (Singleton or Transient).</param>
    /// <param name="args">Arguments forwarded to the constructor of Impl.</param>
    template <typename Interface, typename Impl, typename... Args>
    void bind(DI::Lifetime lifetime, Args&&... args)
    {
        Binding binding;
        binding.lifetime = lifetime;

        if (lifetime == DI::Lifetime::Singleton)
        {
            // Factory lambda captures the 'binding' object and all constructor arguments.
            // The '... args = std::forward<Args>(args)' is C++20 syntax: it expands the parameter pack in the capture list.
            // If this needs to run in C++ 17, the lambda needs to be refactored to use std::apply instead. (something like 'binding->cachedInstance = std::apply(/*lambda in here*/);')
            binding.factory = [binding, ... args = std::forward<Args>(args)]() mutable -> std::shared_ptr<void>
                {
                    // Singleton: only create the instance once and reuse it
                    if (!binding.cachedInstance)
                    {
                        binding.cachedInstance = std::make_shared<Impl>(args...);
                    }
                    return binding.cachedInstance;
                };
        }
        else if (lifetime == DI::Lifetime::Transient)
        {
            // Factory lambda captures constructor args (by move)
            // C++20 lambda capture pack: expands args into capture list
            // If this needs to run in C++ 17, the lambda needs to be refactored to use std::apply instead.
            // (something like 'binding.factory = [argTuple = std::move(argTuple)]() -> std::shared_ptr<void> { return std::apply(/*lambda in here*/);}'
            binding.factory = [... args = std::forward<Args>(args)]() -> std::shared_ptr<void>
                {
                    // Always create a new instance (transient)
                    return std::make_shared<Impl>(args...);
                };
        }

        m_bindings[typeid(Interface)] = std::move(binding);
    }

    /// <summary>
    /// Binds an existing instance directly, instead of creating a new one.
    /// Useful when the instance is pre-created, pre-serialized, or managed externally.
    /// </summary>
    /// <param name="instance">The shared instance to use for injection.</param>
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

    /// <summary>
    /// Resolves a bound interface and returns a shared pointer to the instance.
    /// </summary>
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