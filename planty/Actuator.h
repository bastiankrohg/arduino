#ifndef _ACTUATOR_H
#define _ACTUATOR_H

#include <string>
#include <iostream>
using namespace std; 

#include "Component.h"

class Actuator : public virtual Component {
public: 
    //constructor
    Actuator() : Component{} {
    }
    Actuator(uint8_t rpin) : Component {rpin} {
    }
    Actuator(string name, uint8_t rpin) : Component {name, rpin} {
    }
    Actuator(string name, uint8_t rpin, uint8_t wpin) : Component {name, rpin, wpin} {
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