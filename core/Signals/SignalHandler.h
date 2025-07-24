#pragma once
#include <memory>
#include <unordered_map>
#include <functional>
#include <typeindex>
#include <ISignal.h>
#include <Event.h>

#include <iostream>
#include "ObserverHandler.h"

namespace Signals
{
    class SignalHandler
    {
    public:
        SignalHandler() {}
        ~SignalHandler() {}

        template<typename T>
        Signals::ObserverHandle observeEvent(std::function<void(Event<T>&)> callback)
        {
            std::type_index index = typeid(T);
            size_t id = m_nextObserverId++;

            m_observers[index].emplace_back(
                id,
                [callback](ISignal& evt)
                {
                    callback(static_cast<Event<T>&>(evt));
                }
            );

            return Signals::ObserverHandle{ index, id };
        }

        template<typename T>
        void invokeEvent(const T& data)
        {
            std::type_index index = typeid(T);

            try
            {
                m_eventCache[index] = std::make_shared<Event<T>>(data);
            }
            catch (const std::exception& e)
            {
                std::cerr << "Exception during event creation: " << e.what() << std::endl;
            }

            if (!m_eventCache[index])
            {
                std::cerr << "m_eventCache[index] is nullptr!\n";
                return;
            }

            auto& e = *m_eventCache[index];

            if (m_observers.count(index))
            {
                for (auto& [_, callback] : m_observers[index])
                {
                    callback(e);
                }
            }
        }

        void removeObserver(const Signals::ObserverHandle& handle)
        {
            auto it = m_observers.find(handle.type);
            if (it != m_observers.end())
            {
                auto& vec = it->second;
                vec.erase(std::remove_if(vec.begin(), vec.end(),
                    [&](const auto& pair) { return pair.first == handle.id; }),
                    vec.end());
            }
        }

    private:

        size_t m_nextObserverId = 1;

        using CallbackList = std::vector<std::pair<size_t, std::function<void(ISignal&)>>>;
        std::unordered_map<std::type_index, CallbackList> m_observers;
        std::unordered_map<std::type_index, std::shared_ptr<ISignal>> m_eventCache;
    };
}