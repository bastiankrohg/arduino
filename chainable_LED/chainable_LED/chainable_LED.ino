

#include <ChainableLED.h>
//#include "StatusLED.h"

#define NUM_LEDS  2

ChainableLED leds(D8, D4, NUM_LEDS);

#define indexTemp 1
#define indexWaterlevel 0
#define NUM_LEDS 2
#define MAX_LUM 255
#define MID_LUM 125
#define LOW_LUM 10

byte luminosity = MID_LUM;


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
}
void ledGlobalAlarm(){
  byte pos = 0;
  for (int j=0; j<25; j++){
    for (byte i=0; i<NUM_LEDS; i++)
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

//if ambient temp > threshold then set temperature status led to red, else led is off to save energy
//Temperature light is led with index 0
void setWarningLightTemp(){
  //index, byte red, byte green, byte blue
  leds.setColorRGB(indexTemp, MAX_LUM, 0, 0);  
}
void setNormalStateTemp(){
  leds.setColorRGB(indexTemp, 0, luminosity, 0);
}
//if water level < minimum then set water level status led to red, else led is off to save energy
//Water level light is led with index 1
void setWarningLightWaterlevel(){
  //index, byte red, byte green, byte blue
  leds.setColorRGB(indexWaterlevel, MAX_LUM, 0, 0);  
}
void setNormalStateWaterlevel(){
  leds.setColorRGB(indexWaterlevel, 0, luminosity, 0);
}
void modifyLuminosity(byte lum){
  luminosity = lum;
}



void setup()
{
  leds.init();
  leds.setColorRGB(indexWaterlevel, MID_LUM, 0, MID_LUM);  

}

void loop()
{
  /*
  setNormalStateTemp();
  setNormalStateWaterlevel();
  modifyLuminosity(LOW_LUM);
  delay(2000);
  setNormalStateTemp();
  setNormalStateWaterlevel();
  modifyLuminosity(MID_LUM);
  delay(2000);
  setNormalStateTemp();
  setNormalStateWaterlevel();
  modifyLuminosity(MAX_LUM);
  delay(2000);
  */
  //setAlarmLightTemp();
  /*
  ledSetupColorCycle();
  delay(3000);
  ledGlobalAlarm();
  delay(500);
  setNormalStateTemp();
  delay(3000);
  setNormalStateWaterlevel();
  delay(3000);
  setAlarmLightTemp();
  delay(3000);
  setAlarmLightWaterlevel();
  delay(1000);
  */
  delay(1);

}
