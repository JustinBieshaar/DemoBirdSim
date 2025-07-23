#pragma once
#include "../IBird.h"
#include <iostream>

class Capsule : public IBird {
public:
    Capsule() {}
    ~Capsule(){
        std::cout << "capsule is killed\n";
    }
   std::string getName() { return "Capsule"; };

    std::string getObj_name() const override { return "Capsule.obj"; }
    std::string getTexture() const override { return "none"; }
    float getScale() const override { return 1.0; }
    bool getInvert_uvs() const override { return false; }
    float getMass() const override { return 1.0; }
    float getWingspan() const override { return 1.0; }
    float getMax_speed() const override { return 1.0; }
    float getAcceleration() const override { return 1.0; }
    float getLtd_ratio() const override { return 1.0; }
    float getFlap_rate() const override { return 1.0; }
};