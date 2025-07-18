#pragma once
#include "../IBird.h"

class Goose : public IBird {
public:
    Goose() {}
    std::string getObjName() const override { return "goose.obj"; }
    int getSpeed() const override { return 5; }
    std::string getName() const override { return "goose"; }
};