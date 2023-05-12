#include "Waterlevel.h"



void setup() {
  // put your setup code here, to run once:
  Serial.begin(115200);
  Wire.begin();
}

void loop() {
  // put your main code here, to run repeatedly:
  check();

}
