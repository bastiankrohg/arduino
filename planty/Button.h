#ifndef _BUTTON_H
#define _BUTTON_H

#include "Actuator.h"

class Button : public Actuator{
public:
    //constructors
    Button(string name, uint8_t rpin, uint8_t wpin) : Actuator{name, rpin, wpin} {
    }
    Button(uint8_t rpin) : Actuator{rpin} {
      pinMode(rpin,INPUT);
    }

    //methods
    int readButton(){
      return digitalRead(this->rpin);
    }
    bool boolIsButtonPressed(){
      return (digitalRead(this->rpin)==LOW);
    }
    //is button pressed
  int isButtonPressed(){
    int state = 0;
    if(digitalRead(this->getReadPin())){
      while(digitalRead(this->getReadPin())){
        state = 1;
        return state;
      }
    }
    return state;
  }

};

#endif