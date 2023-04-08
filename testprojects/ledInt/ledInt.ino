//write pin --> LED
int wpin = D7;

void setup() {
  // initialize built-in LED as an output.
  pinMode(wpin, OUTPUT);
}

void loop() {
  digitalWrite(wpin, HIGH);   
  delay(1000);
  digitalWrite(wpin, LOW);
  delay(1000);    
}