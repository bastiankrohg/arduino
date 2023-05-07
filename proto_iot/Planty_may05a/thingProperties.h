// Code generated by Arduino IoT Cloud, DO NOT EDIT.

#include <ArduinoIoTCloud.h>
#include <Arduino_ConnectionHandler.h>

const char DEVICE_LOGIN_NAME[]  = "1996a5b4-6684-451e-b81b-b351bb3be53d";

const char SSID[]               = SECRET_SSID;    // Network SSID (name)
const char PASS[]               = SECRET_OPTIONAL_PASS;    // Network password (use for WPA, or use as key for WEP)
const char DEVICE_KEY[]  = SECRET_DEVICE_KEY;    // Secret device password

void onLedSwitchChange();
void onStartPumpChange();

int humidityValue;
int soilValue;
int tempValue;
bool ledSwitch;
bool startPump;

void initProperties(){

  ArduinoCloud.setBoardId(DEVICE_LOGIN_NAME);
  ArduinoCloud.setSecretDeviceKey(DEVICE_KEY);
  ArduinoCloud.addProperty(humidityValue, READ, ON_CHANGE, NULL);
  ArduinoCloud.addProperty(soilValue, READ, ON_CHANGE, NULL);
  ArduinoCloud.addProperty(tempValue, READ, ON_CHANGE, NULL);
  ArduinoCloud.addProperty(ledSwitch, READWRITE, ON_CHANGE, onLedSwitchChange);
  ArduinoCloud.addProperty(startPump, READWRITE, ON_CHANGE, onStartPumpChange, 1);

}

WiFiConnectionHandler ArduinoIoTPreferredConnection(SSID, PASS);
