/* This file contains summaries for even the most obvious methods as it's acting as a library.
That way each method can be understood without diving into the code. I know some like and other dislike this.
So hence the heads up. ;) */

#pragma once

namespace ECS
{
    class Entity; // forward decleration for owner usage

    class Component
    {
    public:
        virtual ~Component() = default;

        /// <summary>
        /// Owner defined by Entity addComponent.
        /// This will invoke start after owner is set so it can be used to fetch
        /// current owner components (if needed).
        /// </summary>
        void setOwner(Entity* owner)
        {
            m_owner = owner;
            start();
        }

        /// <summary>
        /// Start is called when owner is set so owner components can be fetched at this
        /// point. This can be overwritten.
        /// </summary>
        virtual void start() {}

        virtual void update(float deltaTime) = 0;

    protected:
        Entity* m_owner = nullptr;
    };
}