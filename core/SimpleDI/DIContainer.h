/* This file contains summaries for even the most obvious methods as it's acting as a library.
That way each method can be understood without diving into the code. I know some like and other dislike this.
So hence the heads up. ;) */

#pragma once

#include <functional>
#include <memory>
#include <unordered_map>
#include <typeindex>
#include <stdexcept>
#include <utility>
#include <tuple>
#include <type_traits>
#include <iostream>
#include <vector>

#include "ConstructorTraits.h"
#include "Binding.h"
#include "Lifetime.h"

namespace SimpleDI
{

    template<typename Tuple, std::size_t... I>
    auto generate_args_impl(std::index_sequence<I...>)
    {
        return std::make_tuple(resolve<std::tuple_element_t<I, Tuple>>()...);
    }

    template<typename Tuple>
    auto generate_args()
    {
        return generate_args_impl<Tuple>(std::make_index_sequence<std::tuple_size_v<Tuple>>{});
    }

    /// <summary>
    /// A minimal dependency injection container supporting Singleton, Transient, and pre-instantiated lifetimes.
    /// I've been considering to dive in Boost DI, as I read some cool articles about it. However, as I once in my
    /// life been rejected for using a 3rd party DI library in Unity3D. I since then decided to create my own simple
    /// dependency injection systems to show my understanding of the pattern. ;)
    /// 
    /// At this point, there is NO auto injection. Something I've been trying to do but was consuming too much time.
    /// And as I wanted it to be a simple DI system, it's okay to do it manually (for now). 
    /// </summary>
    class DIContainer
    {
    public:
        /// <summary>
        /// Binds an interface to a concrete implementation type with optional constructor arguments.
        /// </summary>
        /// <param name="lifetime">Lifetime of the created instance (Singleton or Transient).</param>
        /// <param name="args">Arguments forwarded to the constructor of Impl.</param>
        template <typename Interface, typename Impl, typename... ExtraArgs>
        void bind(Lifetime lifetime, ExtraArgs&&... args)
        {
            auto binding = std::make_shared<Binding>();
            binding->lifetime = lifetime;

            if (lifetime == Lifetime::Singleton)
            {
                if constexpr (has_constructor_traits<Impl>::value && std::tuple_size_v<typename SimpleDI::ConstructorTraits<Impl>::Args> > 0)
                {
                    // - With constructor traits
                    // DOES NOT USE EXTRA ARGUMENTS

                    using Args = typename SimpleDI::ConstructorTraits<Impl>::Args;

                    // Create the factory using std::apply to expand resolved dependencies
                    binding->factory = [this, binding]() -> std::shared_ptr<void>
                        {
                            // Singleton: only create the instance once and reuse it
                            if (!binding->cachedInstance)
                            {
                                using Args = typename SimpleDI::ConstructorTraits<Impl>::Args;
                                auto resolvedArgs = [this]<typename... Deps>(std::tuple<Deps...>)
                                {
                                    //((std::cout << "Resolving dependency of type: " << typeid(Deps).name() << std::endl), ...);
                                    return std::make_tuple(resolve<typename Deps::element_type>()...);  // capture `this` for resolve
                                }(Args{});

                                binding->cachedInstance = std::apply([](auto&&... unpacked)
                                    {
                                        return std::make_shared<Impl>(std::forward<decltype(unpacked)>(unpacked)...);
                                    }, std::move(resolvedArgs));
                            }

                            return binding->cachedInstance;
                        };
                }
                else
                {
                    // - Fallback code
                    // 
                    // Factory lambda captures the 'binding' object and all constructor arguments.
                    // The '... args = std::forward<Args>(args)' is C++20 syntax: it expands the parameter pack in the capture list.
                    // If this needs to run in C++ 17, the lambda needs to be refactored to use std::apply instead. (something like 'binding->cachedInstance = std::apply(/*lambda in here*/);')
                    binding->factory = [binding, ... args = std::forward<ExtraArgs>(args)]() mutable -> std::shared_ptr<void>
                        {
                            // Singleton: only create the instance once and reuse it
                            if (!binding->cachedInstance)
                            {
                                binding->cachedInstance = std::make_shared<Impl>(args...);
                            }
                            return binding->cachedInstance;
                        };
                }
            }
            else if (lifetime == Lifetime::Transient)
            {
                if constexpr (has_constructor_traits<Impl>::value && std::tuple_size_v<typename SimpleDI::ConstructorTraits<Impl>::Args> > 0)
                {
                    // - With constructor traits
                    // DOES NOT USE EXTRA ARGUMENTS

                    using Args = typename SimpleDI::ConstructorTraits<Impl>::Args;

                    // Create the factory using constructor traits to automatically resolve dependencies.
                    // This uses std::apply to unpack the resolved dependencies tuple and forward them to the constructor.
                    // Each type in the constructor traits tuple is resolved from the container before constructing the instance.
                    binding->factory = [this]() -> std::shared_ptr<void>
                        {
                            using Args = typename SimpleDI::ConstructorTraits<Impl>::Args;
                            auto resolvedArgs = [this]<typename... Deps>(std::tuple<Deps...>)
                            {
                                return std::make_tuple(resolve<typename Deps::element_type>()...);  // capture `this` for resolve
                            }(Args{});

                            return std::apply([](auto&&... unpacked)
                                {
                                    return std::make_shared<Impl>(std::forward<decltype(unpacked)>(unpacked)...);
                                }, std::move(resolvedArgs));
                        };
                }
                else
                {
                    // - Fallback code
                    // 
                    // Factory lambda captures constructor args (by move)
                    // C++20 lambda capture pack: expands args into capture list
                    // If this needs to run in C++ 17, the lambda needs to be refactored to use std::apply instead.
                    // (something like 'binding.factory = [argTuple = std::move(argTuple)]() -> std::shared_ptr<void> { return std::apply(/*lambda in here*/);}'
                    binding->factory = [... args = std::forward<ExtraArgs>(args)]() -> std::shared_ptr<void>
                        {
                            // Always create a new instance (transient)
                            return std::make_shared<Impl>(args...);
                        };
                }
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
            binding.lifetime = Lifetime::Instance;
            binding.cachedInstance = instance;
            binding.factory = [instance]() -> std::shared_ptr<void>
                {
                    return instance;
                };

            m_bindings[typeid(Interface)] = std::make_shared<Binding>(std::move(binding));
        }

        /// <summary>
        /// Resolves a bound interface and returns a shared pointer to the instance.
        /// </summary>
        template <typename Interface>
        std::shared_ptr<Interface> resolve()
        {
            auto type = typeid(Interface).name();
            auto it = m_bindings.find(typeid(Interface));
            if (it == m_bindings.end())
            {
                for (auto otherContainer : m_sharedContainers)
                {
                    if (!otherContainer->IsBound<Interface>())
                        continue;

                    return otherContainer->resolve<Interface>();
                }

                std::cout << "Type " << typeid(Interface).name() << " not bound!\n";
                return nullptr;
            }
            return std::static_pointer_cast<Interface>(it->second->factory());
        }

        /// <summary>
        /// Links by copying all the links from another container
        /// so they can be used to inject in this container as well.
        /// </summary>
        /// <param name="other"></param>
        void linkContainer(std::shared_ptr<DIContainer> container)
        {
            m_sharedContainers.push_back(container);
        }

        template <typename Interface>
        bool IsBound()
        {
            auto type = typeid(Interface).name();
            auto it = m_bindings.find(typeid(Interface));
            if (it == m_bindings.end())
                return false;

            return true;
        }

    private:
        std::vector<std::shared_ptr<DIContainer>> m_sharedContainers;
        std::unordered_map<std::type_index, std::shared_ptr<Binding>> m_bindings;
    };
}