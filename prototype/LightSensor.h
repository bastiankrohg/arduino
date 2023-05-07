#ifndef _LIGHTSENSOR_H
#define _LIGHTSENSOR_H

#include "Sensor.h"
#include "Component.h"

#include <iostream>
using namespace std;

class LightSensor : public Sensor {
public: 
    //constructor
    LightSensor() : Sensor{} {
    }
    //rpin has to be analog as the light sensor has an analog output
    LightSensor(uint8_t rpin) : Sensor {rpin} {
    }
    LightSensor(string name, uint8_t rpin) : Sensor {name, rpin} {
    }

    //methods
    void init() const {
        cout << "Init light sensor..." << endl; 
        //Component::startSerial();
    }

    int readAnalogLightSensor(){ //analog read
        return analogRead(this->rpin);
        //return analogRead(A0);
    }
    //analog read converted to 0-100
    /*
    int readLightSensor(){ 
        int value = readAnalogLightSensor();
        value = map(value, 0, 800, 0, 100); 
        //Serial.println(value);
        return value;
    }
    */

    void updateMeasurement(){
        this->lastMeasurement = readAnalogLightSensor();
    }

private: 
    int lastMeasurement;
    int baudrate = 9600;
};


#endif