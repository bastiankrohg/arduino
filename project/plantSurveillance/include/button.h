#ifndef _BUTTON_H
#define _BUTTON_H

#include "actuator.h"

class button : public actuator{
public:
    int button_digitalRead(){
        return digitalRead(this->rpin);
    }

private: 
    uint8_t rpin = D6; //read pin

};



void setupButton();

void buttonPushed();

#endif