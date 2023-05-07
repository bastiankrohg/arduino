/*
Pauline DUPUY and Bastian KROHG
4th year INSA Toulouse AE Embedded Systems

C++ Arduino project - Automated / connected greenhouse
*/


#include <iostream>

using namespace std;

#include "rgb_lcd.h"
#include "Button.h"
#include "Display.h"
#include "Led.h"
#include "LightSensor.h"
#include "Soil.h"
#include "WaterPump.h"

//const int pinMoisture = A0;
const int pinLight = A0;
const int pinButtonLED = D7; 
const int pinButtonPump = D8;
const int pinLED = D9;
//const int pinSoil = ?; //pb - need more analog pins or to multiplex A0!

rgb_lcd lcd; 

bool isOverheadLightOn = false;

//Display display(lcd);
Button buttonLED(pinButtonLED);
Button buttonPump(pinButtonPump);
Led led(pinLED);
LightSensor lightSensor(pinLight);
//Soil soilMoisture(pinSoil);
Soil soilMoisture();

void blink(){
  digitalWrite(LED_BUILTIN, HIGH);   // turn the LED on (HIGH is the voltage level)
  delay(1000);                       // wait for a second
  digitalWrite(LED_BUILTIN, LOW);    // turn the LED off by making the voltage LOW
  delay(1000);    
}

void toggleLED(bool isOverheadLightOn, Led led){
  if (isOverheadLightOn){
    Serial.println("LED On");
    led.on();
  } else {
    Serial.println("LED Off");
    led.off();
  }
}

void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);
  lcd.begin(16,2);
  //display.lcd.begin(16,2);

  //pin config
  //pinMode(pinButton, INPUT);
  pinMode(LED_BUILTIN, OUTPUT);
  //display.displayData("Setup Complete");
  //delay(1000);
}

void loop() {
  // put your main code here, to run repeatedly:
  //display.displayData("Hello World!");
  //delay(1000);
  Serial.print("Light sensor value: ");
  Serial.println(lightSensor.readAnalogLightSensor());
  Serial.println();
  delay(1000);
  Serial.print("Temperature and humidity value: ");
  //
  Serial.println();
  delay(1000);
  Serial.print("Soil moisture value: ");
  //
  Serial.println();
  delay(1000);

  //if button pressed, light switches on or off
  if(buttonLED.isButtonPressed()) {
    isOverheadLightOn = !isOverheadLightOn;

    Serial.print("LED Status: ");
    Serial.println(isOverheadLightOn);
    yield();

    //LED On/Off
    toggleLED(isOverheadLightOn, led);
  }
  
  delay(1);

  if (buttonPump.isButtonPressed()){
    Serial.println("Water pump activated");
    while (buttonPump.isButtonPressed()){
    //activate pump

    //update watchdog
    yield();
    }
  }

  delay(1);

  //if () {}
  
  delay(500);
  //display.clearDisplay();
}
