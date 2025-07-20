#pragma once


template<typename T>
class Event : public ISignal
{
public:
    T data;
    Event(const T& d) : data(d) {}
};