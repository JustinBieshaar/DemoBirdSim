#pragma once
#include "../IBird.h"

namespace Birds {
    class Goose : public IBird {
    public:
        Goose() {}
        ~Goose() {}

       std::string getName() const override { return "Goose"; };

       std::string getObj_name() const override { return "Goose-2.obj"; }
       std::string getTexture() const override { return "Goose_Quad_Diffuse.png"; }
       float getScale() const override { return 1.0; }
       bool getInvert_uvs() const override { return true; }
       float getMass() const override { return 1.0; }
       float getWingspan() const override { return 1.0; }
       float getMax_speed() const override { return 1.0; }
       float getAcceleration() const override { return 10.0; }
       float getLtd_ratio() const override { return 1.0; }
       float getFlap_rate() const override { return 1.0; }
   };}