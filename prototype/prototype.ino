#include <iostream>

using namespace std;

#include "rgb_lcd.h"
#include "Display.h"


rgb_lcd lcd; 

Display display(lcd);

void setup() {
  // put your setup code here, to run once:
  display.lcd.begin(16,2);

  //pin config

}

void loop() {
  // put your main code here, to run repeatedly:
  display.displayData("Hello World!");
  delay(1000);
  display.clearDisplay();
}
