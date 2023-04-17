#ifndef _DISPLAY_H
#define _DISPLAY_H

#include "Actuator.h"
#include <string>

class Display : public Actuator {
public: 
    //constructors
    Display() : Actuator {} {
    }
    Display(uint8_t rpin) : Actuator {rpin} {
    }
    Display(string name, uint8_t rpin) : Actuator {name, rpin} {
    }

    //methods
    void init() const;
    void display();
    void updateData();

private: 
    string data[];


};

#endif