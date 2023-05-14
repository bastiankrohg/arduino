#ifndef _SOIL_H
#define _SOIL_H

#define SOIL_MOISTURE_THRESHOLD_LOW 300
#define SOIL_MOISTURE_THRESHOLD_HIGH 1200

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
  bool soilMoistureOK(){
    int soil = this->readSoilSensorValue();
    return (soil >= SOIL_MOISTURE_THRESHOLD_LOW && soil <= SOIL_MOISTURE_THRESHOLD_HIGH);
  }
  bool soilMoistureLow(){
    return (readSoilSensorValue() <= SOIL_MOISTURE_THRESHOLD_LOW);
  }
  bool soilMoistureHigh(){
    return (readSoilSensorValue() >= SOIL_MOISTURE_THRESHOLD_HIGH);
  }

private: 

};

//void setupSoilMoistureSensor();

//int readSoil();

#endif