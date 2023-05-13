#ifndef _SOIL_H
#define _SOIL_H

#define SOIL_MOISTURE_THRESHOLD 300

class Soil : public Sensor {
public: 
  //constructors:
  Soil() : Sensor{} {
  }
  Soil(uint8_t rpin) : Sensor{rpin} {
  }

  /*
  int readSoilMoistureSensor(){
    return analogRead(this->rpin);
  }
  */
  int readSoilSensorValue(){
    return this->readAnalogSensorValue();  
  }
  bool soilMoistureUnderThreshold(){
    return (readSoilSensorValue() <= SOIL_MOISTURE_THRESHOLD);
  }

private: 

};

//void setupSoilMoistureSensor();

//int readSoil();

#endif