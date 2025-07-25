/*
* This file contains summaries for even the most obvious methods as it's acting as a library.
* That way each method can be understood without diving into the code. I know some like and other dislike this.
* So hence the heads up. ;) 
* 
* Also.. I know this type of system can have multiple namings like; 
* Signal / Event / Message... So far I've had many discussions on how to name it.
* But whenever I personally create this kind of systems, I like to call it signals.
* 
* But my opinion is not extremely strong though. It's just when I need to make the decision, I can easily adapt. ;P
*/

#pragma once
#include <memory>
#include <unordered_map>
#include <functional>
#include <typeindex>
#include <ISignal.h>
#include <Signal.h>

#include <iostream>
#include "ObserverHandler.h"

namespace Signals
{
    /// <summary>
    /// Handles signals to be observed or invoked.
    /// </summary>
    class SignalHandler
    {
    public:
        SignalHandler() {}
        ~SignalHandler() {}

        /// <summary>
        /// Observe a signal to wait for it to be invoked.
        /// Ivokation can be done from anywhere whoever has access to this signal handler.
        /// 
        /// Caution; ensure to remove listener upon deletion to prevent kaboom's from happening ;)
        /// </summary>
        /// <returns>ObserverHandle which is a cached struct used to remove the observation.</returns>
        template<typename T>
        Signals::ObserverHandle observeSignal(std::function<void(Signal<T>&)> callback)
        {
            std::type_index index = typeid(T);
            size_t id = m_nextObserverId++;

            m_observers[index].emplace_back(
                id,
                [callback](ISignal& evt)
                {
                    callback(static_cast<Signal<T>&>(evt));
                }
            );

            return Signals::ObserverHandle{ index, id };
        }

        /// <summary>
        /// Invoke any signal using a struct as data.
        /// So, invokeSignal struct A will invoke struct A to all observers who registered themselves to it.
        /// </summary>
        template<typename T>
        void invokeSignal(const T& data)
        {
            std::type_index index = typeid(T);

            try
            {
                m_signalCache[index] = std::make_shared<Signal<T>>(data);
            }
            catch (const std::exception& e)
            {
                std::cerr << "Exception during signal creation: " << e.what() << std::endl;
            }

            if (!m_signalCache[index])
            {
                std::cerr << "m_signalCache[index] is nullptr!\n";
                return;
            }

            auto& e = *m_signalCache[index];

            if (m_observers.count(index))
            {
                for (auto& [_, callback] : m_observers[index])
                {
                    callback(e);
                }
            }

            std::cout << "Signal: " << typeid(T).name() << " has been invoked!\n";
        }

        /// <summary>
        /// Remove observation of a signal.
        /// </summary>
        /// <param name="handle"></param>
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
        /// <summary>
        /// Storing the observer id to have a uniquer ID in case it must be removed.
        /// </summary>
        size_t m_nextObserverId = 1;

        // Just a better readable name ;)
        using CallbackList = std::vector<std::pair<size_t, std::function<void(ISignal&)>>>;

        std::unordered_map<std::type_index, CallbackList> m_observers;
        std::unordered_map<std::type_index, std::shared_ptr<ISignal>> m_signalCache;
    };
}