// Auto-generated: bird instance.
// DO NOT ADJUST MANUALLY!

#pragma once
#include "../IBird.h"

namespace Birds {
    class Robin : public IBird {
    public:
        Robin() {}
        ~Robin() {}

       std::string getName() const override { return "Robin"; };

       float getMass() const override { return 1.0; }
       float getWingspan() const override { return 2.0; }
       float getAcceleration() const override { return 150.0; }
       float getFlap_rate() const override { return 1.0; }
       float getLtd_ratio() const override { return 1.0; }
       float getMax_speed() const override { return 1.0; }
       bool getInvert_uvs() const override { return false; }
       std::string getObj_name() const override { return "Robin-bird.obj"; }
       float getScale() const override { return 1.0; }
       std::string getTexture() const override { return "robin-texture.png"; }
   };
}