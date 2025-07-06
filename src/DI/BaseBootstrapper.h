#pragma once

#include "DIContainer.h"

class BaseBootstrapper
{
public:
    BaseBootstrapper() : m_container(std::make_unique<DIContainer>()) {}
    virtual ~BaseBootstrapper() = default;

    // Bind all necessary interfaces and implementations
    virtual void configureBindings() = 0;

    // Optionally resolve shared services or do post-binding setup
    virtual void initialize() {}

protected:
    std::unique_ptr<DIContainer> m_container;
};