#ifndef _WATERPUMP_H
#define _WATERPUMP_H

#include "Actuator.h"

class WaterPump : public Actuator {
public: 

  WaterPump() : Actuator{}{
  }

  WaterPump(uint8_t wpin) : Actuator{}{
    this->wpin = wpin;
  }

  void on(){
    digitalWrite(this->wpin, HIGH);   // turn the water pump on (HIGH is the voltage level)
  }
  void off(){
    digitalWrite(this->wpin, LOW);   // turn the LED on (HIGH is the voltage level)
  }
  void activateIrrigationSystem(int delay_seconds){
    this->on();
    delay(delay_seconds * 1000);
    this->off();
  }
  void increaseIrrigation(){
    wateringperiod++;
  }
  void irrigate(){
    this->on();
    delay(this->wateringperiod * 1000);
    this->off();
  }

  void activateIrrigationSystem2s(){
    this->on();
    delay(2000);
    this->off();
    delay(1000);
  }
private: 
  //watering period in bursts of 'wateringperiod' seconds at a time
  int wateringperiod;

};

#endif