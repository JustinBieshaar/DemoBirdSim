#pragma once


template<typename T>
class Event : public IEvent
{
public:
    T data;
    Event(const T& d) : data(d) {}
};