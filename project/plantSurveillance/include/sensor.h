#ifndef _SENSOR_H
#define _SENSOR_H

#include <string>
using namespace std; 

#include "component.h"

class sensor : public component {
public: 
    sensor() : component {} {
    }
    //constructor with only rpin
    sensor(string name, uint8_t rpin) : component{ name } {
        this->rpin = rpin;
    } 

    void init();
//private:
//protected:
};

#endif