#include <sys/types.h>
#include <sys/_stdint.h>
#ifndef _LED_H
#define _LED_H

#include <ChainableLED.h>
#include <Arduino.h>
#include "Actuator.h"



//Chainable leds
#define indexTemp 0
#define indexWaterlevel 1
#define NUM_LEDS 2
#define MAX_LUM 255
#define MID_LUM 125
#define LOW_LUM 10
#define PIN_STATUS_LED D8
#define PIN_STATUS_LED_CLK_PIN D8
#define PIN_STATUS_LED_DATA_PIN D4

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

private: 

};

/*
class LEDs : public Actuator {
public: 
  void setAssociatedLedChain(ChainableLED leds){
    this->leds = leds;
  }

  void ledGlobalAlarm(){
    uint8_t pos = 0;
    for (int j=0; j<25; j++){
      for (uint8_t i=0; i<NUM_LEDS; i++)
      {
        if (i==pos)
          this->leds.setColorRGB(i, MAX_LUM, 0, 0);  
        else
          this->leds.setColorRGB(i, 0, 0, MAX_LUM); 
      }
      delay(250);

      pos = (pos+1) % NUM_LEDS;
    }
  }
  //if ambient temp > threshold then set temperature status led to red, else led is off/luminosity @ 10 to save energy
    //Temperature light is led with index 1
  void setWarningLightTemp(){
    //index, byte red, byte green, byte blue
    this->leds.setColorRGB(indexTemp, MAX_LUM, 0, 0);  
  }
  void setNormalStateTempLight(){
    this->leds.setColorRGB(indexTemp, 0, luminosity, 0);
  }
  //if water level < minimum then set water level status led to red, else led is off/luminosity @ 10 to save energy
    //Water level light is led with index 0
  void setWarningLightWaterlevel(){
    //index, byte red, byte green, byte blue
    this->leds.setColorRGB(indexWaterlevel, MAX_LUM, 0, 0);  
  }
  void setNormalStateWaterlevelLight(){
    this->leds.setColorRGB(indexWaterlevel, 0, luminosity, 0);
  }
  void setWarningLightSoil(){
    this->leds.setColorRGB(indexWaterlevel, MAX_LUM, 0, MAX_LUM);  
  }
  void modifyLuminosity(uint8_t lum){
    this->luminosity = lum;
  }
  void ledSetupColorCycle(){
    this->leds.init();
    float hue = 0.0;
    boolean up = true;
    for (int j=0; j<20; j++){
      for (uint8_t i=0; i<NUM_LEDS; i++)
          leds.setColorHSL(i, hue, 1.0, 0.5);
        
        delay(50);
          
        if (up)
          hue+= 0.025;
        else
          hue-= 0.025;
          
        if (hue>=1.0 && up)
          up = false;
        else if (hue<=0.0 && !up)
          up = true;
    }

    //Set initial luminosity and set status this->leds to normal state
    modifyLuminosity(luminosity);
    setNormalStateTempLight();
    setNormalStateWaterlevelLight();
  }

  friend class TemperatureSensor;

private: 
  uint8_t luminosity;
  ChainableLED leds;
};
*/




#endif