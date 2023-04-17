#ifndef _ACTUATOR_H
#define _ACTUATOR_H

#include <string>
#include <iostream>
using namespace std; 

#include "component.h"

class actuator : public component {
public: 
    //constructor
    actuator() : component{} {
    }
    actuator(uint8_t rpin) : component {rpin} {
    }
    actuator(string name, uint8_t rpin) : component {name, rpin} {
    }
    actuator(string name, uint8_t rpin, uint8_t wpin) : component {name, rpin, wpin} {
    }

    //methods
    void init();
    /*
    int getReadPin(){
        return this->rpin; 
    }
    int getWritePin(){
        return this->wpin; 
    }
    string getName(){
        return this->name;
    }
    */
//private: 
//protected:
};

#endif