#ifndef _SENSOR_H
#define _SENSOR_H

#include <string>
using namespace std; 

#include "Component.h"

class Sensor : public virtual Component {
public: 
    //constructor
    Sensor() : Component {} {
    }
    Sensor(uint8_t rpin) : Component {rpin} {
    }
    Sensor(string name, uint8_t rpin) : Component{ name, rpin } {
    } 

    void init();

    int readAnalogSensorValue(){
      return analogRead(this->rpin);
    }
    int readDigitalSensorValue(){
      return digitalRead(this->rpin);
    }
    void updateSensorValue(int value){
      this->sensorValue = value;
    }
//private:
protected:
  int sensorValue;
};

#endif