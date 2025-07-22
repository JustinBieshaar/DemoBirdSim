#pragma once
#include <string>

class IBird
{
public:
    IBird() {}
   virtual std::string getObj_name() const = 0;
   virtual std::string getTexture() const = 0;
   virtual float getScale() const = 0;
   virtual bool getInvert_uvs() const = 0;
   virtual float getMass() const = 0;
   virtual float getWingspan() const = 0;
   virtual float getMax_speed() const = 0;
   virtual float getAcceleration() const = 0;
   virtual float getLtd_ratio() const = 0;
   virtual float getFlap_rate() const = 0;
};