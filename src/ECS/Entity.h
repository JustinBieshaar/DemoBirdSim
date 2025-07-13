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

    /// <summary>
    /// Adds a component of type T to the entity.
    /// Constructs the component with the provided arguments.
    /// </summary>
    template<typename T, typename ...Args>
    std::shared_ptr<T> addComponent(Args&& ...args)
    {
        auto component = std::make_shared<T>(std::forward<Args>(args)...);
        m_components[typeid(T)] = component;
        return component;
    }

    /// <summary>
    /// Adds an existing component (already created) to the entity.
    /// </summary>
    void addComponent(std::shared_ptr<Component> component)
    {
        m_components[typeid(*component)] = component;
    }

    /// <summary>
    /// Retrieves a pointer to the component of type T, or nullptr if not found. ;)
    /// </summary>
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

    /// <summary>
    /// Method name says it all ;P
    /// </summary>
    template<typename T>
    bool hasComponent()
    {
        return m_components.find(typeid(T)) != m_components.end();
    }

    /// <summary>
    /// Method name says it all ;P
    /// </summary>
    template<typename T>
    bool tryGetComponent(T*& ref)
    {
        auto it = m_components.find(typeid(T));
        if (it != m_components.end())
        {
            ref = static_cast<T*>(it->second.get()); // cast Component* to T*, Unsafe cast; but I am assuming correct type
            return true;
        }
        return false;
    }

    /// <summary>
    /// Loops through all components and returns all components of type you give dynamically.
    /// </summary>
    template<typename T>
    std::vector<std::shared_ptr<T>> getAllComponentsOfType()
    {
        std::vector<std::shared_ptr<T>> result;
        for (const auto& [type, component] : m_components)
        {
            if (auto casted = std::dynamic_pointer_cast<T>(component))
            {
                result.push_back(casted);
            }
        }

        return result;
    }

    void updateAllComponents(float deltaTime)
    {
        for (const auto& [type, component] : m_components)
        {
            component->update(deltaTime);
        }
    }

    virtual void update(float deltaTime) = 0;

private:
    // Stores components mapped by their type, using Run time type index (RTTI)
	std::unordered_map<std::type_index, std::shared_ptr<Component>> m_components;
};