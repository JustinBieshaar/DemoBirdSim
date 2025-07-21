#pragma once
#include <string>

class IBird
{
public:
    IBird() {}
   virtual int getMass() const = 0;
   virtual int getWingspan() const = 0;
   virtual int getAcceleration() const = 0;
   virtual int getFlap_rate() const = 0;
   virtual int getLtd_ratio() const = 0;
   virtual int getMax_speed() const = 0;
   virtual std::string getObj_name() const = 0;
   virtual std::string getTexture() const = 0;
};