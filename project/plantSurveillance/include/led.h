#ifndef _LED_H
#define _LED_H

#include <Arduino.h>
#include "Actuator.h"

class Led : public Actuator {
public:
    //constructors
    

    //methods
    void blinkInternalLED();

    /******Work in progress*******/
    void setupLED(int pin);

    void startLED();
    void stopLED();

    void setColor(); //arg?
    /****************************/
private: 

};

void blinkInternalLEDWOClass();




#endif