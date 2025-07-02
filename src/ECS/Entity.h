#pragma once
#include <cstdint>
#include <memory>
#include <typeindex>
#include <unordered_map>
#include "Components/Component.h"

class Entity
{
public:
    template<typename T, typename... Args>
    T& addComponent(Args&&... args);

    template<typename T>
    T* getComponent();

    template<typename T>
    bool HasComponent();

    template<typename T>
    bool HasComponent(T& ref);

private:
	std::unordered_map<std::type_index, std::shared_ptr<Component>> m_components;
};