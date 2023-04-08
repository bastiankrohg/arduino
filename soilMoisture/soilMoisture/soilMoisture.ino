/*
Soil moisture sensor
https://www.elecfreaks.com/octopus-soil-moisture-sensor-brick.html
Analog output (yellow wire)
GND (black)
Power (red)
*/

void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);
}

void loop() {
  // put your main code here, to run repeatedly:
  //Testing with A0 but should choose other pin as this is also used by light sensor!
  int value = analogRead(A0);
  value = map(value, 0, 800, 0, 10);
  Serial.println(value);
  delay(1000);
}
