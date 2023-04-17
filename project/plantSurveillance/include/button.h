#ifndef _BUTTON_H
#define _BUTTON_H

#include "actuator.h"

class button : public actuator{
public:
    //constructors
    button(string name, uint8_t rpin, uint8_t wpin) : actuator{name, rpin, wpin} {
    }
    button(uint8_t rpin) : actuator{rpin} {
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