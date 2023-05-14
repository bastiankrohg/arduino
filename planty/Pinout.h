#ifndef _PINOUT_H
#define _PINOUT_H

/**THIRDPARTY LIBRARIES********************************************************************************/
#include <iostream>
#include "String.h"

#include <rgb_lcd.h>
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
#include "Waterlevel.h"
#include "Buzzer.h"
#include "TempHumidity.h"

/**PIN LAYOUT********************************************************************************/
//#define PIN_LIGHT_SENSOR = A0
//Waterlevel I2C --> Wire.h
//LCD Screen I2C --> Wire.h
#define PIN_SOIL A0
#define PIN_RELAY D3
#define PIN_WATERPUMP D7 //only needs to be high by default to power water pump
#define PIN_BUZZER D9 //need to test
#define PIN_TEMP_HUMIDITY D7
#define PIN_STATUS_LED D8
#define PIN_STATUS_LED_CLK_PIN D8
#define PIN_STATUS_LED_DATA_PIN D4
#define PIN_BUTTON_PUMP_CTRL D6

/**TEMPERATURE AND HUMIDITY SENSOR CONFIGURATION********************************************************************************/
//from <DHT.h>
#define DHTTYPE DHT22   // DHT 22  (AM2302)
#define DHTPIN D7       // what pin we're connected to（DHT10 and DHT20 don't need define it）

/**SOIL MOISTURE SENSOR CONFIGURATION********************************************************************************/
#define SOIL_MOISTURE_THRESHOLD 300

/**LED CHAIN CONFIGURATION********************************************************************************/
#define NUM_LEDS 2

/**OBJECT CREATION********************************************************************************/
rgb_lcd lcd; 
//Display display(lcd); //problem
Button buttonPumpCtrl(PIN_BUTTON_PUMP_CTRL);
//LightSensor lightSensor(PIN_LIGHT_SENSOR);
//Soil soilMoisture;
Soil soilMoisture(PIN_SOIL);
WaterPump waterpump(PIN_RELAY);
ChainableLED ledchain(PIN_STATUS_LED_CLK_PIN, PIN_STATUS_LED_DATA_PIN, NUM_LEDS);
//LEDs leds;
Buzzer buzzer(PIN_BUZZER);
TemperatureSensor temperatureSensor(DHTPIN, DHTTYPE);
HumiditySensor humiditySensor(DHTPIN,DHTTYPE);
WaterlevelSensor waterlevelSensor;

/**INIT FUNCTION********************************************************************************/
//initializes pins and lcd, as well as the initial state of the relay and buzzer!
void init(){
  //Waterpump / relay
  pinMode(PIN_RELAY, OUTPUT);
  //Button is configured as input in Button.h
  pinMode(PIN_BUTTON_PUMP_CTRL, INPUT);

  //watering is off by default
  digitalWrite(PIN_RELAY,LOW);
  
  //buzzer off by default
  buzzer.off();

  //lcd
  lcd.begin(16, 2);
  // Print a message to the LCD.
  lcd.print("I'm thirsty!");

}


/**GLOBAL VARIABLES********************************************************************************/
uint8_t luminosity = LOW_LUM;
bool waterlevelLow = false;
bool temperatureWarning = false;
bool humidityWarning = false;
bool soilWarning = false;

String displaymessage="";
String temperature_message="";
String humidity_message="";
String soil_moisture_message="";
String waterlevel_message="";
String warning_message=" USER WARNING: ";
String error_message=" ERROR: ";

/**SUPPORTING FUNCTIONS********************************************************************************/

  /**LED FUNCTIONS********************************************************************************/
/*void ledGlobalAlarmSimple(){
  for (int j=0; j<3; j++){
    uint8_t pos = 0;
    for (uint8_t i=0; i<NUM_LEDS; i++)
    {
      if (i==pos)
        ledchain.setColorRGB(i, MAX_LUM, 0, 0);  
      else
        ledchain.setColorRGB(i, 0, 0, MAX_LUM); 
    }
    delay(250);

    pos = (pos+1) % NUM_LEDS;
  }
}*/

void ledGlobalAlarm(){
  uint8_t pos = 0;
  for (int j=0; j<25; j++){
    for (uint8_t i=0; i<NUM_LEDS; i++)
    {
      if (i==pos)
        ledchain.setColorRGB(i, MAX_LUM, 0, 0);  
      else
        ledchain.setColorRGB(i, 0, 0, MAX_LUM); 
    }
    delay(250);

    pos = (pos+1) % NUM_LEDS;
  }
}
//if ambient temp > threshold then set temperature status led to red, else led is off/luminosity @ 10 to save energy
  //Temperature light is led with index 1
void setWarningLightTemp(){
  //index, byte red, byte green, byte blue
  ledchain.setColorRGB(indexTemp, MAX_LUM, 0, 0);  
}
void setNormalStateTempLight(){
  ledchain.setColorRGB(indexTemp, 0, luminosity, 0);
}
//if water level < minimum then set water level status led to red, else led is off/luminosity @ 10 to save energy
  //Water level light is led with index 0
void setWarningLightWaterlevel(){
  //index, byte red, byte green, byte blue
  ledchain.setColorRGB(indexWaterlevel, MAX_LUM, 0, 0);  
}
void setNormalStateWaterlevelLight(){
  ledchain.setColorRGB(indexWaterlevel, 0, luminosity, 0);
}
/*void setWarningLightSoil(){
  ledchain.setColorRGB(indexWaterlevel, MAX_LUM, 0, MAX_LUM);  
}
void setNormalStateSoilLight(){
  //ledchain.setColorRGB(indexWaterlevel, MAX_LUM, 0, MAX_LUM);  
}*/

void modifyLuminosity(uint8_t lum){
  luminosity = lum;
}
void ledSetupColorCycle(){
  ledchain.init();
  float hue = 0.0;
  boolean up = true;
  for (int j=0; j<20; j++){
    for (uint8_t i=0; i<NUM_LEDS; i++)
      ledchain.setColorHSL(i, hue, 1.0, 0.5);
      
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
void toggleLED(bool isLedOn, Led led){
  if (isLedOn){
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
  buzzer.buzz();

}
//temp too high
  //Temperature status led => RED
  //Short beep with buzzer
void alert_temperatureHigh(){
  setWarningLightTemp();
  //buzzer
  buzzer.buzz();

}
//if soil moisture low
  //=>water lvl status led => purple
/*
void alert_soilMoistureLow(){
  setWarningLightSoil();
  //buzzer
  buzzer.buzz();
}*/

/**DISPLAY FUNCTIONS********************************************************************************/
/*
void lcd_display_msg_autoscroll(rgb_lcd lcd, string displaymsg){
  lcd.begin(16,2);

      // set the cursor to (0,0):
    lcd.setCursor(0, 0);
    
    
    // print from 0 to 9:
    for (int thisChar = 0; thisChar < 10; thisChar++) {
        lcd.print(thisChar);
        delay(500);
    }

    // set the cursor to (16,1):
    lcd.setCursor(16, 1);
    // set the display to automatically scroll:
    lcd.autoscroll();
    
    // print from 0 to 9:
    for (int thisChar = 0; thisChar < 10; thisChar++) {
        lcd.print(thisChar);
        delay(500);
    }
    
    // turn off automatic scrolling
    lcd.noAutoscroll();

    // clear screen for the next loop:
    lcd.clear();
}*/
String createDisplayMessage(){
  //get soil moisture data
  soil_moisture_message=" Soil Moisture: ";
  soil_moisture_message += soilMoisture.readSoilSensorValue();
  //get temperature and humidity data
  temperature_message=" Temperature: ";
  temperature_message+=temperatureSensor.readTemperature(false); //true==Fahrenheit, false==Celsius
  humidity_message=" Humidity: ";
  humidity_message+=humiditySensor.readHumidity();
  //get water level data
  waterlevel_message=waterlevelSensor.waterlevelPercentString();
  //concatenate display message
  displaymessage = "";
  displaymessage += soil_moisture_message;
  displaymessage += temperature_message;
  displaymessage += humidity_message;
  displaymessage += waterlevel_message;

  //error / warning messages

  return displaymessage;
}
/*void debug_print_in_serial(){
  Serial.println("Button: ");
  Serial.println(buttonPumpCtrl.isButtonPressed());
  Serial.println("Soil: ");
  Serial.println(soilMoisture.soilMoistureLow());
  Serial.println("Button + Soil: ");
  Serial.println((buttonPumpCtrl.isButtonPressed() || soilMoisture.soilMoistureLow()));
  Serial.println("!waterlvl low: ");
  Serial.println(!waterlevelLow);
  Serial.println("!soilMoistureHigh: ");
  Serial.println(!soilMoisture.soilMoistureHigh());
  Serial.println("Full condition: ");
  Serial.println(!waterlevelLow && !soilMoisture.soilMoistureHigh() && (buttonPumpCtrl.isButtonPressed() || soilMoisture.soilMoistureLow()));
}*/


#endif