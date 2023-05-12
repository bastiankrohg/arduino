#ifndef BUZZER_H_
#define BUZZER_H_

#include "Actuator.h"

class Buzzer : public Actuator{
public:
    //constructors
    Buzzer(string name, uint8_t rpin, uint8_t wpin) : Actuator{name, rpin, wpin} {
    }
    Buzzer(uint8_t wpin) : Actuator{} {
      this->wpin = wpin;
      this->initBuzzer();
    }

    //methods
    void initBuzzer(){
      pinMode(this->wpin, OUTPUT);
    }
    void buzz(){
      digitalWrite(this->wpin, HIGH);
      delay(1000);
      digitalWrite(this->wpin, LOW);
      delay(1000);
    }
};



#endif