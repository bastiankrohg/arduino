#include "esp_camera.h"
#include "FS.h"
#include "SD_MMC.h"
#include "esp_timer.h"
#include "img_converters.h"
#include "Arduino.h"

#define BUTTON_PIN 14
#define LED_PIN 4

// Function to capture a photo
void capturePhoto() {
  camera_fb_t * fb = esp_camera_fb_get();
  if (!fb) {
    Serial.println("Camera capture failed");
    return;
  }

  // Optional: Save to SPIFFS/SD or stream
  Serial.printf("Captured image: %dx%d, %d bytes\n", fb->width, fb->height, fb->len);

  // Release the buffer
  esp_camera_fb_return(fb);
}
bool lastButtonState = HIGH;
unsigned long lastDebounceTime = 0;
const unsigned long debounceDelay = 50;

void setup() {
  Serial.begin(115200);
  pinMode(BUTTON_PIN, INPUT_PULLUP);
  pinMode(LED_PIN, OUTPUT);
}

void loop() {
  int reading = digitalRead(BUTTON_PIN);

  if (reading != lastButtonState) {
    lastDebounceTime = millis();
  }

  if ((millis() - lastDebounceTime) > debounceDelay) {
    if (reading == LOW && lastButtonState == HIGH) {
      // Button just pressed
      digitalWrite(LED_PIN, !digitalRead(LED_PIN)); // Toggle LED for feedback
      Serial.println("Button pressed — taking photo...");
      capturePhoto();
    }
  }

  lastButtonState = reading;
  digitalWrite(LED_PIN, lastButtonState == LOW ? HIGH : LOW); // On when pressed

}