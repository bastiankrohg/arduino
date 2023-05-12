#include <sys/_stdint.h>
#ifndef _LED_H
#define _LED_H

#include <Arduino.h>
#include "Actuator.h"

#define indexTemp 1
#define indexWaterlevel 0
#define NUM_LEDS 2
#define MAX_LUM 255
#define MID_LUM 125
#define LOW_LUM 10

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