#include "Entity.h"

template<typename T, typename ...Args>
T& Entity::addComponent(Args && ...args)
{
    auto component = std::make_shared<T>(std::forward<Args>(args)...);
    components[typeid(T)] = component;
    return *component;
}

template<typename T>
T* Entity::getComponent()
{
    auto it = components.find(typeid(T));
    if (it != components.end())
    {
        return static_cast<T*>(it->second.get());
    }
    return nullptr;
}

template<typename T>
bool Entity::HasComponent()
{
    return components.find(typeid(T)) != components.end();
}

template<typename T>
bool Entity::HasComponent(T& ref)
{
    if (HasComponent<T>())
    {
        ref = components.find(typeid(T));
        return true;
    }

    return false;
}
