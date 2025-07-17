#pragma once
#include <string>

class Bird
{
public:
    virtual std::string getObjName() const = 0;
    virtual int getSpeed() const = 0;
    virtual std::string getName() const = 0;
    virtual ~Bird() {}
};