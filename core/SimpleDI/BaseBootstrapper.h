#pragma once

#include "DIContainer.h"

namespace SimpleDI
{
    /// <summary>
    /// Abstract base class for setting up and initializing dependency injection bindings.
    /// </summary>
    class BaseBootstrapper
    {
    public:
        BaseBootstrapper() : m_container(std::make_unique<DIContainer>()) {}
        virtual ~BaseBootstrapper() = default;

        /// <summary>
        /// Pure virtual method to bind all necessary interfaces to implementations.
        /// This must be overridden by derived classes to configure dependencies.
        /// </summary>
        virtual void configureBindings() = 0;

        template <typename Interface>
        std::shared_ptr<Interface> resolve()
        {
            return m_container->resolve<Interface>();
        }

    protected:
        std::unique_ptr<DIContainer> m_container;
    };
}