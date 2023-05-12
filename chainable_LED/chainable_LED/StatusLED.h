#ifndef _STATUS_LED_H
#define _STATUS_LED_H

#include <Arduino.h>
#include <ChainableLED.h>
#include "Actuator.h"


/*
class StatusLED : public Actuator, public ChainableLED {
public:
  StatusLED(uint8_t clk_pin, uint8_t data_pin, uint8_t num_leds) : ChainableLED{clk_pin, data_pin, num_leds} {
  }

  //methods
  void blink();

  void statusLEDStartupCycle(){
    this->leds.init();
    for (int j=0; j<3; j++){
      float hue = 0.0;
      boolean up = true;

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
  }
  
  //if ambient temp > threshold then set temperature status led to red, else led is off to save energy
  //Temperature light is led with index 0
  void setAlarmLightTemp(){
    //index, byte red, byte green, byte blue
    leds.setColorRGB(indexTemp, 255, 0, 0);  
  }
  //if water level < minimum then set water level status led to red, else led is off to save energy
  //Water level light is led with index 1
  void setAlarmLightWaterlevel(){
    //index, byte red, byte green, byte blue
    leds.setColorRGB(indexWaterlevel, 255, 0, 0);  
  }

  void setLEDS(ChainableLED leds){
    this->leds = leds;
  }

private: 
  ChainableLED leds;

};
*/


#endif