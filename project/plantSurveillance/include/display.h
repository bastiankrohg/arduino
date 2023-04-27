#ifndef _DISPLAY_H
#define _DISPLAY_H

#include "Actuator.h"
#include <string>

#include "rgb_lcd.h"
//Communication with the Grove display uses I2C

class Display : public Actuator {
public: 
    //constructors
    Display() : Actuator {} {
    }
    Display(uint8_t rpin) : Actuator {rpin} {
    }
    Display(string name, uint8_t rpin) : Actuator {name, rpin} {
    }

protected:
    //methods
    void init() const;
    void display();
    void updateData();

private: 
    rgb_lcd lcd;
    string data[];
};

#endif