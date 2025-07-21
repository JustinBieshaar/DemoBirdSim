#pragma once
#include <memory>
#include <unordered_map>
#include <functional>
#include <typeindex>
#include <ISignal.h>
#include <Event.h>

#include <iostream>

class SignalHandler
{
public:
    // Observers: map from event type -> list of callbacks
    std::unordered_map<std::type_index, std::vector<std::function<void(ISignal&)>>> observers;

    // Event cache (for reusing/reconstructing)
    std::unordered_map<std::type_index, std::shared_ptr<ISignal>> eventCache;

    template<typename T>
    void observeEvent(std::function<void(Event<T>&)> callback)
    {
        std::type_index index = typeid(T);
        observers[index].emplace_back(
            [callback](ISignal& evt)
            {
                callback(static_cast<Event<T>&>(evt));
            }
        );
    }

    template<typename T>
    void invokeEvent(const T& data)
    {
        std::type_index index = typeid(T);

        std::cout << "Creating event for type: " << index.name() << std::endl;

        try
        {
            eventCache[index] = std::make_shared<Event<T>>(data); // crash likely here
        }
        catch (const std::exception& e)
        {
            std::cerr << "Exception during event creation: " << e.what() << std::endl;
        }

        if (!eventCache[index])
        {
            std::cerr << "eventCache[index] is nullptr!\n";
            return;
        }

        auto& event = *eventCache[index];

        if (observers.count(index))
        {
            for (auto& callback : observers[index])
            {
                callback(*eventCache[index]);
            }
        }
    }
};