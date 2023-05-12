#include "WaterPump.h"

#define RELAY_PIN D3
//#define pinWP D7
//#define pinWP D5

WaterPump waterpump(RELAY_PIN);

void setup() {
  // put your setup code here, to run once:
  pinMode(RELAY_PIN, OUTPUT);
  //pinMode(pinWP, OUTPUT);
  //pinMode(pinWP, OUTPUT);
  //digitalWrite(pinWP, HIGH);
}

void loop() {
  // put your main code here, to run repeatedly:
  //waterpump.activateIrrigationSystem2s();
  /*
  digitalWrite(RELAY_PIN, HIGH); // turn the relay on (HIGH is the voltage level)
  delay(5000);   // wait for 3 seconds
  digitalWrite(RELAY_PIN, LOW);   // turn the relay off by making the voltage LOW
  delay(5000);   // wait for 3 seconds
  */
  
  //Activates water pump for 2s bursts
  waterpump.activateIrrigationSystem2s();
}
