#include <sys/_stdint.h>
#ifndef _LED_H
#define _LED_H

#include <Arduino.h>
#include "Actuator.h"

class Led : public Actuator {
public:
    //constructors
    Led() : Actuator{} {
    }
    Led(uint8_t wpin) : Actuator{} {
      this->wpin = wpin;
    }

    //methods
    void blinkInternalLED();

    void off();
    void on();

    /******Work in progress*******/
    void setColor(); //arg?
    /****************************/
private: 

};





#endif