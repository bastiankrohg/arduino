/*****************************************************
Pauline DUPUY and Bastian KROHG
4th year INSA Toulouse AE Embedded Systems

C++ Arduino project - Automated / connected greenhouse

  Operational status of system components: 
    Soil moisture sensor:                     .
    Water Level indicator:                    .
    LCD Screen:                               .
    Water Pump + Relay:                       .
    Buzzer:                                   .
    Temperature&Humidity sensor:              .
    LED Chain:                                OK (consider trying class integration)
    Button:                                   .
*****************************************************/

/**THIRDPARTY LIBRARIES********************************************************************************/
#include <iostream>
#include "String.h"

#include "rgb_lcd.h"
#include <DHT.h>
#include <ChainableLED.h>

using namespace std;

/**OWN LIBRARIES********************************************************************************/
#include "Button.h"
#include "Display.h"
#include "Led.h"
#include "LightSensor.h"
#include "Soil.h"
#include "WaterPump.h"
#include "Buzzer.h"

/**PIN LAYOUT********************************************************************************/
#define PIN_SOIL A0
//Waterlevel I2C --> Wire.h
//LCD Screen I2C --> Wire.h
#define PIN_RELAY D3
#define PIN_WATERPUMP D7 //only needs to be high by default to power water pump
#define PIN_BUZZER D6
//#define PIN_TEMP_HUMIDITY D7
#define PIN_STATUS_LED D8
#define PIN_STATUS_LED_CLK_PIN D8
#define PIN_STATUS_LED_DATA_PIN D4
#define PIN_BUTTON_PUMP_CTRL D9 //need to test if it works as it is on the grove UART pin

/**********************************************************************************/
//TO BE REMOVED
const int pinLight = A0;
//const int pinButtonLED = D7; 
//const int pinButtonPump = D8;
const int pinLED = D9;
const int pinWPump = D8;
//const int pinSoil = ?; //pb - need more analog pins or to multiplex A0!
/**********************************************************************************/

/**TEMPERATURE AND HUMIDITY SENSOR CONFIGURATION********************************************************************************/
//temp & humidity sensor
#define DHTTYPE DHT22   // DHT 22  (AM2302)
#define DHTPIN D7     // what pin we're connected to（DHT10 and DHT20 don't need define it）
DHT dht(DHTPIN, DHTTYPE);   //   DHT11 DHT21 DHT22
#if defined(ARDUINO_ARCH_AVR)
    #define debug  Serial
#elif defined(ARDUINO_ARCH_SAMD) ||  defined(ARDUINO_ARCH_SAM)
    #define debug  SerialUSB
#else
    #define debug  Serial
#endif

/**SOIL MOISTURE SENSOR CONFIGURATION********************************************************************************/
#define SOIL_MOISTURE_THRESHOLD 300
//to be removed
#define soilThreshold 300

/**LED CHAIN CONFIGURATION********************************************************************************/
#define NUM_LEDS 2

/**OBJECT CREATION********************************************************************************/
rgb_lcd lcd; 
//Display display(lcd); //problem
//Button buttonLED(pinButtonLED);
//Button buttonPump(pinButtonPump);
Button buttonPumpCtrl(PIN_BUTTON_PUMP_CTRL);
//Led led(pinLED);
LightSensor lightSensor(pinLight);
Soil soilMoisture;
WaterPump waterpump(PIN_RELAY);
ChainableLED leds(PIN_STATUS_LED_CLK_PIN, PIN_STATUS_LED_DATA_PIN, NUM_LEDS);
Buzzer buzzer(PIN_BUZZER);


/**GLOBAL VARIABLES********************************************************************************/
uint8_t luminosity = LOW_LUM;

bool isOverheadLightOn = false;

String displaymessage="";
String temperature_message=" Temperature: ";
String humidity_message=" Humidity: ";
String soil_moisture_message=" Soil Moisture: ";
String waterlevel_message=" Water Level: ";
String warning_message="USER WARNING: ";
String error_message="ERROR: ";

/**SUPPORTING FUNCTIONS********************************************************************************/
/**LED FUNCTIONS********************************************************************************/
void ledGlobalAlarm(){
  uint8_t pos = 0;
  for (int j=0; j<25; j++){
    for (uint8_t i=0; i<NUM_LEDS; i++)
    {
      if (i==pos)
        leds.setColorRGB(i, MAX_LUM, 0, 0);  
      else
        leds.setColorRGB(i, 0, 0, MAX_LUM); 
    }
    delay(250);

    pos = (pos+1) % NUM_LEDS;
  }
}
//if ambient temp > threshold then set temperature status led to red, else led is off/luminosity @ 10 to save energy
//Temperature light is led with index 1
void setWarningLightTemp(){
  //index, byte red, byte green, byte blue
  leds.setColorRGB(indexTemp, MAX_LUM, 0, 0);  
}
void setNormalStateTempLight(){
  leds.setColorRGB(indexTemp, 0, luminosity, 0);
}
//if water level < minimum then set water level status led to red, else led is off/luminosity @ 10 to save energy
//Water level light is led with index 0
void setWarningLightWaterlevel(){
  //index, byte red, byte green, byte blue
  leds.setColorRGB(indexWaterlevel, MAX_LUM, 0, 0);  
}
void setNormalStateWaterlevelLight(){
  leds.setColorRGB(indexWaterlevel, 0, luminosity, 0);
}
void setWarningLightSoil(){
  leds.setColorRGB(indexWaterlevel, MAX_LUM, 0, MAX_LUM);  
}
void modifyLuminosity(uint8_t lum){
  luminosity = lum;
}
void ledSetupColorCycle(){
  leds.init();
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

  //Set initial luminosity and set status leds to normal state
  modifyLuminosity(luminosity);
  setNormalStateTempLight();
  setNormalStateWaterlevelLight();
}
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

/**ALARM FUNCTIONS********************************************************************************/
//if any problem at all: display message on screen + LED_BUILTIN activated
void displayAlert();
//water low
  //=> Buzzer + Red and Blue flashing leds for 10 sec
void alert_waterLvlLow(){
  setWarningLightWaterlevel();
  //buzzer
}
//temp too high
  //Temperature status led => RED
  //Short beep with buzzer
void alert_temperatureHigh(){
  setWarningLightTemp();
  //buzzer
}
//if soil moisture low
  //=>water lvl status led => purple
void alert_soilMoistureLow(){
  setWarningLightSoil();
  //buzzer
}







/**SETUP********************************************************************************/
void setup() {
  //initialize LED chain
  ledSetupColorCycle();

  //Waterpump / relay
  pinMode(PIN_RELAY, OUTPUT);
  //pinMode(PIN_WATERPUMP, OUTPUT);
  //keep pump off by default
  digitalWrite(PIN_RELAY,LOW);

  //Button is configured as input in Button.h
  
}



/**MAIN********************************************************************************/
void loop() {
  // put your main code here, to run repeatedly:
  
  //ledGlobalAlarm();
  delay(1);
  /*
  if (buttonPumpCtrl.isButtonPressed()){
    waterpump.activateIrrigationSystem2s();
    yield();
  } else {
    yield();
  }
  */
  buzzer.buzz();
  delay(2000);



  //TODO

  //Read sensors to obtain new data, store temporarily
  /********************************/

  //Create Display message for lcd screen
  /********************************/

  //Display message
  /********************************/


  //Actions:
  //if water level too low, activate alarm and block watering functionality

  //if temperature too high, notify caretaker --> By msg / email? 

  //if soil moisture too low, activate water until moisture level normalized

  //if button pushed, override alerts to activate waterpump
      //should this work even though water level is too low???
  


}
