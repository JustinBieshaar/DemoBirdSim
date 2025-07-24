#pragma once

namespace ECS
{
    class Entity; // forward decleration for owner usage

    class Component
    {
    public:
        virtual ~Component() = default;

        void setOwner(Entity* owner)
        {
            m_owner = owner;
            start();
        }

        virtual void start() {}

        virtual void update(float deltaTime) = 0;

    protected:
        Entity* m_owner = nullptr;
    };
}