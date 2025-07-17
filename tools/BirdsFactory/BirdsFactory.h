// BirdFactory.h
#pragma once
#include "Birds/Bird.h"
#include <memory>
#include <unordered_map>
#include <functional>
#include <string>

class BirdsFactory
{
public:
    static BirdsFactory& getInstance();

    std::shared_ptr<Bird> createBird(const std::string& name);

    void registerBird(const std::string& name, std::function<std::shared_ptr<Bird>()> constructor);

private:
    std::unordered_map<std::string, std::function<std::shared_ptr<Bird>()>> registry;
    BirdsFactory() {}
};