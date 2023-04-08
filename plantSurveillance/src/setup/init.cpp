#include "init.h"

void initArduino(){

}


void initSensors(){
    //sensor setup
    setupTempSensor();
    setupHumiditySensor();
    setupLightSensor();
    setupSoilMoistureSensor();

    //setup lights, buttons and actuators
    setupButton();
    setupLED();

    //Configure WIFI
    setupWifi();
}

void init(){
    initArduino();
    initSensors();
}
