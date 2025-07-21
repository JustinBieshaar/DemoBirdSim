#pragma once
#include "../IBird.h"

class Robin : public IBird {
public:
    Robin() {}
    int getMass() const override { return 1; }
    int getWingspan() const override { return 1; }
    int getAcceleration() const override { return 1; }
    int getFlap_rate() const override { return 1; }
    int getLtd_ratio() const override { return 1; }
    int getMax_speed() const override { return 1; }
    std::string getObj_name() const override { return "Robin-bird"; }
    std::string getTexture() const override { return "robin-texture.png"; }
};