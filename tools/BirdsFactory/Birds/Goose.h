#pragma once
#include "../IBird.h"

class Goose : public IBird {
public:
    Goose() {}
   std::string getName() { return "Goose"; };

    std::string getObj_name() const override { return "Goose.obj"; }
    std::string getTexture() const override { return "Goose_Quad_Diffuse.png"; }
    float getScale() const override { return 1.0; }
    bool getInvert_uvs() const override { return true; }
    float getMass() const override { return 1.0; }
    float getWingspan() const override { return 1.0; }
    float getMax_speed() const override { return 1.0; }
    float getAcceleration() const override { return 1.0; }
    float getLtd_ratio() const override { return 1.0; }
    float getFlap_rate() const override { return 1.0; }
};