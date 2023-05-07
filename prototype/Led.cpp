#include "Led.h"

void Led::blinkInternalLED(){
    digitalWrite(LED_BUILTIN, HIGH);   // turn the LED on (HIGH is the voltage level)
    delay(1000);                       // wait for a second
    digitalWrite(LED_BUILTIN, LOW);    // turn the LED off by making the voltage LOW
    delay(1000);      
}

void Led::off(){
  digitalWrite(this->wpin, LOW);   // turn the LED off (LOW is the voltage level)
}

void Led::on(){
  digitalWrite(this->wpin, HIGH);   // turn the LED on (HIGH is the voltage level)
}
