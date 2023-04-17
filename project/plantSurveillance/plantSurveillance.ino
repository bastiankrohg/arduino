/*
* C++ project 
* 4th Year AE-SE - Group 1
* Pauline DUPUY and Bastian KROHG
*
* Smart irrigation system
*   => Can be used to automate plant care and do
*       surveillance of your pet plants' health
*/

//sensors
#include "include/sensor.h"
#include "include/sunlight.h"
//actuators
#include "include/actuator.h"
#include "include/button.h"
#include "include/display.h"
#include "include/led.h"


void setup() {
  // put your setup code here, to run once:
    pinMode(LED_BUILTIN, OUTPUT);
}

void loop() {
  // put your main code here, to run repeatedly:
  blinkInternalLED();
}
