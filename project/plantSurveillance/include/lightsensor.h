#ifndef _LIGHTSENSOR_H
#define _LIGHTSENSOR_H

#include "sensor.h"
#include "component.h"

#include <iostream>
using namespace std;

class lightSensor : public sensor {
public: 
    //constructor
    lightSensor() : sensor{} {
    }
    //rpin has to be analog as the light sensor has an analog output
    lightSensor(uint8_t rpin) : sensor {rpin} {
    }
    lightSensor(string name, uint8_t rpin) : sensor {name, rpin} {
    }

    //methods
    void init() const {
        cout << "Init light sensor..." << endl; 
        //component::startSerial();
    }

    int readAnalogLightSensor(){ //analog read
        return analogRead(this->rpin);
    }
    //analog read converted to 0-100
    int readLightSensor(){ 
        int value = readAnalogLightSensor();
        value = map(value, 0, 800, 0, 100); 
        //Serial.println(value);
        return value;
    }

    void updateMeasurement(){
        this->lastMeasurement = readLightSensor();
    }

private: 
    int lastMeasurement;
    int baudrate = 9600;
};


#endif