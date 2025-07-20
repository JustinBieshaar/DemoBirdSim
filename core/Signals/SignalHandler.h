#pragma once
#include <memory>
#include <unordered_map>
#include <functional>
#include <typeindex>
#include <ISignal.h>
#include <Event.h>

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

        // Reconstruct the event (overwrite if already exists)
        eventCache[index] = std::make_shared<Event<T>>(data);
        auto& event = *eventCache[index];

        // Call observers
        if (observers.count(index))
        {
            for (auto& callback : observers[index])
            {
                callback(*eventCache[index]);
            }
        }
    }
};