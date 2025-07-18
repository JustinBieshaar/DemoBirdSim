#pragma once
#include "../IBird.h"

class Gull : public IBird {
public:
    Gull() {}
    std::string getObjName() const override { return "gull.obj"; }
    int getSpeed() const override { return 7; }
    std::string getName() const override { return "gull"; }
};