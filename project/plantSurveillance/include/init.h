#ifndef _INIT_H
#define _INIT_H

#include <Arduino.h>

#include "Led.h"
#include "Soil.h"
#include "Temp.h"
#include "Humidity.h"
#include "wifi.h"
#include "Button.h"
#include "LightSensor.h"


void initArduino();
void initSensors();
void init();

#endif