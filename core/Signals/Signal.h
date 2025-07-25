#pragma once
#include <type_traits>
#include <ISignal.h>

namespace Signals
{
    /// <summary>
    /// This is the base signal and most likely the most commonly used signal within this sytem.
    /// This signal holds a struct value which can be observed using the signal handler.
    /// </summary>
    /// <typeparam name="T"></typeparam>
    template<typename T>
    class Signal : public ISignal
    {
        static_assert(!std::is_reference_v<T>, "Signal<T>: T must not be a reference type");
        static_assert(std::is_copy_constructible_v<T>, "Signal<T>: T must be copy-constructible");

    public:
        T data;
        Signal(const T& d) : data(d) {}
    };
}