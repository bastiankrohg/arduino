#include "esp_camera.h"
#include <WiFi.h>
#include "esp_timer.h"
#include "Arduino.h"
#include <WebServer.h>

#define CAMERA_MODEL_AI_THINKER
#include "camera_pins.h"

#define BUTTON_PIN 14
#define LED_PIN 4

// Replace with your WiFi credentials
const char* ssid = "bastiphone";
const char* password = "bastiphone";

// Globals
WebServer server(80);
camera_fb_t * last_fb = nullptr;
bool lastButtonState = HIGH;
unsigned long lastDebounceTime = 0;
const unsigned long debounceDelay = 50;
int pictureCount = 0;

void capturePhoto() {
  Serial.println(">>> Entered capturePhoto() function");
  if (last_fb != nullptr) {
    esp_camera_fb_return(last_fb);
    last_fb = nullptr;
  }

  Serial.println("Attempting to capture image...");

  last_fb = esp_camera_fb_get();
  if (!last_fb) {
    Serial.println("Camera capture failed");
    return;
  }

  //digitalWrite(LED_PIN, HIGH);
  //delay(100); // Quick blink for feedback
  //digitalWrite(LED_PIN, LOW);

  pictureCount++;
  Serial.printf("Photo #%d captured: %dx%d, %d bytes\n", pictureCount, last_fb->width, last_fb->height, last_fb->len);
}

void handleRoot() {
  String html = "<!DOCTYPE html><html><head>";
  html += "<meta http-equiv='refresh' content='5'>";
  html += "<title>ESP32-CAM</title></head><body>";
  html += "<h1>Photo Server</h1>";
  html += "<img src='/photo' width='320'><p>";
  html += "Photos taken: " + String(pictureCount) + "</p></body></html>";
  server.send(200, "text/html", html);
}

void handlePhoto() {
  if (!last_fb) {
    server.send(503, "text/plain", "No photo available yet.");
    return;
  }

  WiFiClient client = server.client();
  if (!client) {
    Serial.println("No client connected!");
    return;
  }

  // Send headers manually
  client.println("HTTP/1.1 200 OK");
  client.println("Content-disposition: inline; filename=capture.jpg");
  client.println("Content-type: image/jpeg");
  client.println("Content-length: " + String(last_fb->len));
  client.println(); // end headers

  client.write(last_fb->buf, last_fb->len);

  Serial.println("✔️ Sent photo to client");
}

void setup() {
  Serial.begin(115200);
  pinMode(BUTTON_PIN, INPUT_PULLUP);
  pinMode(LED_PIN, OUTPUT);

  // Camera config
  camera_config_t config;
  config.ledc_channel = LEDC_CHANNEL_0;
  config.ledc_timer = LEDC_TIMER_0;
  config.pin_d0 = Y2_GPIO_NUM;
  config.pin_d1 = Y3_GPIO_NUM;
  config.pin_d2 = Y4_GPIO_NUM;
  config.pin_d3 = Y5_GPIO_NUM;
  config.pin_d4 = Y6_GPIO_NUM;
  config.pin_d5 = Y7_GPIO_NUM;
  config.pin_d6 = Y8_GPIO_NUM;
  config.pin_d7 = Y9_GPIO_NUM;
  config.pin_xclk = XCLK_GPIO_NUM;
  config.pin_pclk = PCLK_GPIO_NUM;
  config.pin_vsync = VSYNC_GPIO_NUM;
  config.pin_href = HREF_GPIO_NUM;
  config.pin_sccb_sda = SIOD_GPIO_NUM;
  config.pin_sccb_scl = SIOC_GPIO_NUM;
  config.pin_pwdn = PWDN_GPIO_NUM;
  config.pin_reset = RESET_GPIO_NUM;
  config.xclk_freq_hz = 20000000;
  config.frame_size = FRAMESIZE_QVGA;
  config.pixel_format = PIXFORMAT_JPEG;
  config.fb_location = CAMERA_FB_IN_PSRAM;
  config.jpeg_quality = 12;
  config.fb_count = 1;

  // Init camera
  esp_err_t err = esp_camera_init(&config);
  if (err != ESP_OK) {
    Serial.printf("Camera init failed with error 0x%x", err);
    return;
  }

  capturePhoto();  // Try capturing one photo right after setup

  // Connect to WiFi
  WiFi.begin(ssid, password);
  Serial.print("Connecting to WiFi");
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }
  Serial.println("\nWiFi connected");
  Serial.println(WiFi.localIP());

  // Start server
  server.on("/", handleRoot);
  server.on("/photo", HTTP_GET, handlePhoto);
  server.begin();
}

void loop() {
  static int lastStableState = HIGH;
  static int lastReading = HIGH;
  static unsigned long lastDebounceTime = 0;

  int currentReading = digitalRead(BUTTON_PIN);

  if (currentReading != lastReading) {
    lastDebounceTime = millis();  // reset debounce timer
  }

  if ((millis() - lastDebounceTime) > debounceDelay) {
    if (currentReading != lastStableState) {
      lastStableState = currentReading;

      if (currentReading == LOW) {
        Serial.println("Button press detected — capturing photo...");
        capturePhoto();
        //digitalWrite(LED_PIN, !digitalRead(LED_PIN)); // Toggle LED
      }
    }
  }

  lastReading = currentReading;

  server.handleClient();
}