//write pin --> LED
//int wpin = D7;
int wpin = D3;
//read pin --> button
//int rpin = D6;
int rpin = D9;

void setup() {
  // initialize built-in LED as an output.
  pinMode(wpin, OUTPUT);
  pinMode(rpin, INPUT);
}

void loop() {
  if (digitalRead(rpin)==HIGH){
    digitalWrite(wpin, HIGH);   
  } else {
    digitalWrite(wpin, LOW);    
  }
}