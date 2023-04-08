//Status: Not doing as I want, LEDs not responding when uploading

//Lib: https://github.com/pjpmarques/ChainableLED
#include <ChainableLED.h>


/*
Datasheet:
  Vcc = 5v --> convert from 3v3 on output?
  Op current: 20 mA
  Comm protocol: Serial

  Should be connected to Base shield D7 (or D8) 
*/

#define NUM_LEDS 2

ChainableLED leds(7,8,NUM_LEDS);

void setup() {
  leds.init();
}

float hue = 0.0;
boolean up = true;

void loop() {
  for (byte i=0; i<NUM_LEDS; i++){
    leds.setColorHSL(i,hue,1.0,0.5);
  }
  delay(50);
  
  if (up){
    hue+= 0.025;
  } else{
    hue-= 0.025;
  }

  if (hue>=1.0 && up){
    up = false;
  } else {
    up = true;
  }
}
