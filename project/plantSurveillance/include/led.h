#ifndef _LED_H
#define _LED_H

#include <Arduino.h>

void blinkInternalLED();

/******Work in progress*******/
void setupLED(int pin);

void startLED();
void stopLED();

void setColor(); //arg?
/****************************/

#endif