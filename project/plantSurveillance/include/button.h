#ifndef _BUTTON_H
#define _BUTTON_H

#include "Actuator.h"

class Button : public Actuator{
public:
    //constructors
    Button(string name, uint8_t rpin, uint8_t wpin) : Actuator{name, rpin, wpin} {
    }
    Button(uint8_t rpin) : Actuator{rpin} {
    }

    //methods
    int readButton(){
        return digitalRead(this->rpin);
    }
    bool isButtonPushed(){
        return (digitalRead(this->rpin)==HIGH);
    }

    /*
    void updateLastValue(){
        this->lastValue = readButton();
    }
private: 
    int lastValue;
    */ 
};

#endif