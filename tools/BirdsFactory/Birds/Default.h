#pragma once
#include "../IBird.h"

class Default : public IBird {
public:
    Default() {}
    int getMass() const override { return 1; }
    int getWingspan() const override { return 1; }
    int getAcceleration() const override { return 1; }
    int getFlap_rate() const override { return 1; }
    int getLtd_ratio() const override { return 1; }
    int getMax_speed() const override { return 1; }
    std::string getObj_name() const override { return "capsule"; }
    std::string getTexture() const override { return "none"; }
};