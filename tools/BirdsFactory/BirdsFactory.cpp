#include "BirdsFactory.h"

BirdsFactory& BirdsFactory::getInstance()
{
    static BirdsFactory instance;
    return instance;
}

void BirdsFactory::registerBird(const std::string& name, std::function<std::shared_ptr<Bird>()> constructor)
{
    registry[name] = constructor;
}

std::shared_ptr<Bird> BirdsFactory::createBird(const std::string& name)
{
    if (registry.count(name))
    {
        return registry[name]();
    }
    return nullptr;
}