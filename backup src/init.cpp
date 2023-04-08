#include "../include/init.h"

void initESP8266(){
    //Configure WIFI connectivity of the board
    setupWifi();
}


void initSensors(){
    //sensor setup
    setupTempSensor();
    setupHumiditySensor();
    setupLightSensor();
    setupSoilMoistureSensor();

    //setup lights, buttons and actuators
    setupButton();
    setupLED(7);
}

void init(){
    initESP8266();
    initSensors();
}
