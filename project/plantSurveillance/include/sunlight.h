#ifndef _SUNLIGHT_H
#define _SUNLIGHT_H

#include "sensor.h"

void setupLightSensor();

int readLightSensor();

class lightSensor : public sensor {

};


#endif