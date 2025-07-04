#pragma once
#include <cstdint>
#include <memory>
#include <typeindex>
#include <unordered_map>
#include "Components/Component.h"

class Entity
{
public:

    virtual ~Entity() = default;

    template<typename T, typename ...Args>
    T& addComponent(Args && ...args)
    {
        auto component = std::make_shared<T>(std::forward<Args>(args)...);
        m_components[typeid(T)] = component;
        return *component;
    }

    void addComponent(std::shared_ptr<Component> component)
    {
        m_components[typeid(*component)] = component;
    }

    template<typename T>
    T* getComponent()
    {
        auto it = m_components.find(typeid(T));
        if (it != m_components.end())
        {
            return static_cast<T*>(it->second.get());
        }
        return nullptr;
    }

    template<typename T>
    bool hasComponent()
    {
        return m_components.find(typeid(T)) != m_components.end();
    }

    template<typename T>
    bool tryGetComponent(T& ref)
    {
        auto it = m_components.find(typeid(T));
        if (it != m_components.end())
        {
            ref = *static_cast<T*>(it->second.get());
            return true;
        }
        return false;
    }


private:
	std::unordered_map<std::type_index, std::shared_ptr<Component>> m_components;
};