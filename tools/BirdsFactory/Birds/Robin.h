#pragma once
#include "../IBird.h"

class Robin : public IBird {
public:
    Robin() {}
    std::string getObjName() const override { return "robin.obj"; }
    int getSpeed() const override { return 10; }
    std::string getName() const override { return "robin"; }
};