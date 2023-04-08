#ifndef _INIT_H
#define _INIT_H

#include <Arduino.h>

#include "led.h"
#include "soil.h"
#include "temp.h"
#include "humidity.h"
#include "wifi.h"
#include "button.h"
#include "sunlight.h"


void initArduino();
void initSensors();
void init();

#endif