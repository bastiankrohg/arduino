#define BUTTON_PIN 14
#define LED_PIN 4

void setup() {
  Serial.begin(115200);
  pinMode(BUTTON_PIN, INPUT_PULLUP);
  pinMode(LED_PIN, OUTPUT);
}

void loop() {
  int buttonState = digitalRead(BUTTON_PIN);
  digitalWrite(LED_PIN, buttonState == LOW ? HIGH : LOW); // On when pressed

  delay(10);  // Optional small delay
}