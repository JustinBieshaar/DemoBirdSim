#pragma once
#include "../IBird.h"

class RobinBlue : public IBird {
public:
    RobinBlue() {}
    std::string getObj_name() const override { return "Robin-bird.obj"; }
    std::string getTexture() const override { return "robin-texture-blue.png"; }
    float getScale() const override { return 1.0; }
    bool getInvert_uvs() const override { return false; }
    float getMass() const override { return 3.0; }
    float getWingspan() const override { return 1.0; }
    float getMax_speed() const override { return 1.0; }
    float getAcceleration() const override { return 1.0; }
    float getLtd_ratio() const override { return 1.0; }
    float getFlap_rate() const override { return 1.0; }
};