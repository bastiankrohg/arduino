int pin = 7;
//int pin = D7;

void setup() {
  pinMode(pin, OUTPUT);
}

void loop() {
  digitalWrite(pin, HIGH);   
  delay(1000);               
  digitalWrite(pin, LOW);    
  delay(1000);               
}