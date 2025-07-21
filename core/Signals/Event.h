#pragma once
#include <type_traits>
#include <ISignal.h>

template<typename T>
class Event : public ISignal
{
    static_assert(!std::is_reference_v<T>, "Event<T>: T must not be a reference type");
    static_assert(std::is_copy_constructible_v<T>, "Event<T>: T must be copy-constructible");

public:
    T data;
    Event(const T& d) : data(d) {}
};