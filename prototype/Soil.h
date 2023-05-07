#ifndef _SOIL_H
#define _SOIL_H

class Soil : public Sensor {
public: 
  //constructors:
  Soil() : Sensor{} {
  }
  Soil(uint8_t rpin) : Sensor{rpin} {
  }

  int readSoilMoistureSensor(){
    return analogRead(this->rpin);
  }

private: 

};

void setupSoilMoistureSensor();

int readSoil();

#endif