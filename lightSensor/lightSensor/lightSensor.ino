/*
Light sensor returns analog value
Should be connected to pin A0 on grove base shield
*/

void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);
}

void loop() {
  // put your main code here, to run repeatedly:
  int value = analogRead(A0);
  //0 < Analog Value < 800, mapping it to be between 0 and 10
  value = map(value, 0, 800, 0, 10);
  Serial.println(value);
  delay(1000);
}
