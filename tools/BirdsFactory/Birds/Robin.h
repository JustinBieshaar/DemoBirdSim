#pragma once
#include "../IBird.h"

namespace Birds {
    class Robin : public IBird {
    public:
        Robin() {}
        ~Robin() {}

       std::string getName() const override { return "Robin"; };

       std::string getObj_name() const override { return "Robin-bird.obj"; }
       std::string getTexture() const override { return "robin-texture.png"; }
       float getScale() const override { return 1.0; }
       bool getInvert_uvs() const override { return false; }
       float getMass() const override { return 1.0; }
       float getWingspan() const override { return 1.0; }
       float getMax_speed() const override { return 1.0; }
       float getAcceleration() const override { return 150.0; }
       float getLtd_ratio() const override { return 1.0; }
       float getFlap_rate() const override { return 1.0; }
   };}