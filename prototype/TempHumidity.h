#ifndef _TEMPHUMIDITY_H
#define _TEMPHUMIDITY_H

#include <DHT.h>

#define Threshold_Hot 30 //°C
#define Threshold_Cold 10 //°C
#define Threshold_Air_Dry 60.0//A définir
#define Threshold_Air_Wet 70.0//A définir
#define No_Error 0
#define Temperature_Cold 4
#define Temperature_Hot 5
#define Air_Dry 6
#define Air_Wet 7

class TemperatureSensor : public DHT {
public: 
  TemperatureSensor(uint8_t pin, uint8_t type) : DHT{pin, type} {
  }

  int warningTemperature(){
    int error = No_Error ; 
    if (this->temperature<Threshold_Cold) {
      error = Temperature_Cold;
    }
    else if(this->temperature>Threshold_Hot) {
      error = Temperature_Hot;
    }
    return error;
  }

  void updateTempData(int temperature){
    this->temperature = temperature;
  }
private: 
  int temperature;

};

class HumiditySensor : public DHT {
public:
  HumiditySensor(uint8_t pin, uint8_t type) : DHT{pin, type} {
  }

  int warningHumidity(){
    int error = No_Error ; 
    if (this->humidity<Threshold_Air_Dry) {
      error = Air_Dry;
    }
    else if(this->humidity>Threshold_Air_Wet) {
      error = Air_Wet;
    }
    return error;
  }
  void updateHumidityData(int humidity){
    this->humidity = humidity;
  }
private:
  int humidity;

};


#endif