#ifndef _WATERLEVEL_H
#define _WATERLEVEL_H

#include <Wire.h>
#include "String.h"

unsigned char low_data[8] = {0};
unsigned char high_data[12] = {0};

#define NO_TOUCH       0xFE
#define THRESHOLD      100
//#define THRESHOLD_PERCENT 0
#define THRESHOLD_PERCENT 10
#define ATTINY1_HIGH_ADDR   0x78
#define ATTINY2_LOW_ADDR   0x77

class WaterlevelSensor : public Sensor {
public: 
    void getHigh12SectionValue(void) {
    memset(high_data, 0, sizeof(high_data));
    Wire.requestFrom(ATTINY1_HIGH_ADDR, 12);
    while (12 != Wire.available());

    for (int i = 0; i < 12; i++) {
      high_data[i] = Wire.read();
    }
    delay(10);
  }

  void getLow8SectionValue(void) {
    memset(low_data, 0, sizeof(low_data));
    Wire.requestFrom(ATTINY2_LOW_ADDR, 8);
    while (8 != Wire.available());

    for (int i = 0; i < 8 ; i++) {
      low_data[i] = Wire.read(); // receive a byte as character
    }
    delay(10);
  }
  int getWaterlevel(){
    uint32_t touch_val = 0;
    uint8_t trig_section = 0;

    getLow8SectionValue();
    getHigh12SectionValue();

    for (int i = 0 ; i < 8; i++) {
      if (low_data[i] > THRESHOLD) {
        touch_val |= 1 << i;
      }
    }

    for (int i = 0 ; i < 12; i++) {
      if (high_data[i] > THRESHOLD) {
        touch_val |= (uint32_t)1 << (8 + i);
      }
    }

    while (touch_val & 0x01)
    {
      trig_section++;
      touch_val >>= 1;
    }
    return trig_section*5;
  }

  String waterlevelPercentString(){
    int level = this->getWaterlevel();
    String water_level = "Water level: ";
    water_level += level;
    water_level += "% ";
    return water_level;
  }

  bool waterlevelOK(){
    return (this->getWaterlevel()>=THRESHOLD_PERCENT);
  }



  void waterlevelPercentWLoop(){
    /*
    int sensorvalue_min = 250;
    int sensorvalue_max = 255;
    */
    while (1)
    {
      uint32_t touch_val = 0;
      uint8_t trig_section = 0;

      getLow8SectionValue();
      getHigh12SectionValue();

      for (int i = 0 ; i < 8; i++) {
        if (low_data[i] > THRESHOLD) {
          touch_val |= 1 << i;
        }
      }

      for (int i = 0 ; i < 12; i++) {
        if (high_data[i] > THRESHOLD) {
          touch_val |= (uint32_t)1 << (8 + i);
        }
      }

      while (touch_val & 0x01)
      {
        trig_section++;
        touch_val >>= 1;
      }
      Serial.print("Water level = ");
      Serial.print(trig_section * 5);
      Serial.println("% ");
      delay(1000);
    }
  }

  void check(){
    int sensorvalue_min = 250;
    int sensorvalue_max = 255;
    int low_count = 0;
    int high_count = 0;
    while (1)
    {
      uint32_t touch_val = 0;
      uint8_t trig_section = 0;
      low_count = 0;
      high_count = 0;
      getLow8SectionValue();
      getHigh12SectionValue();

      Serial.println("low 8 sections value = ");
      for (int i = 0; i < 8; i++)
      {
        Serial.print(low_data[i]);
        Serial.print(".");
        if (low_data[i] >= sensorvalue_min && low_data[i] <= sensorvalue_max)
        {
          low_count++;
        }
        if (low_count == 8)
        {
          Serial.print("      ");
          Serial.print("PASS");
        }
      }
      Serial.println("  ");
      Serial.println("  ");
      Serial.println("high 12 sections value = ");
      for (int i = 0; i < 12; i++)
      {
        Serial.print(high_data[i]);
        Serial.print(".");

        if (high_data[i] >= sensorvalue_min && high_data[i] <= sensorvalue_max)
        {
          high_count++;
        }
        if (high_count == 12)
        {
          Serial.print("      ");
          Serial.print("PASS");
        }
      }

      Serial.println("  ");
      Serial.println("  ");

      for (int i = 0 ; i < 8; i++) {
        if (low_data[i] > THRESHOLD) {
          touch_val |= 1 << i;

        }
      }
      for (int i = 0 ; i < 12; i++) {
        if (high_data[i] > THRESHOLD) {
          touch_val |= (uint32_t)1 << (8 + i);
        }
      }

      while (touch_val & 0x01)
      {
        trig_section++;
        touch_val >>= 1;
      }
      Serial.print("water level = ");
      Serial.print(trig_section * 5);
      Serial.println("% ");
      Serial.println(" ");
      Serial.println("*********************************************************");
      delay(1000);
    }
  }
};

void getHigh12SectionValue(void)
{
  memset(high_data, 0, sizeof(high_data));
  Wire.requestFrom(ATTINY1_HIGH_ADDR, 12);
  while (12 != Wire.available());

  for (int i = 0; i < 12; i++) {
    high_data[i] = Wire.read();
  }
  delay(10);
}

void getLow8SectionValue(void)
{
  memset(low_data, 0, sizeof(low_data));
  Wire.requestFrom(ATTINY2_LOW_ADDR, 8);
  while (8 != Wire.available());

  for (int i = 0; i < 8 ; i++) {
    low_data[i] = Wire.read(); // receive a byte as character
  }
  delay(10);
}

void check()
{
  int sensorvalue_min = 250;
  int sensorvalue_max = 255;
  int low_count = 0;
  int high_count = 0;
  while (1)
  {
    uint32_t touch_val = 0;
    uint8_t trig_section = 0;
    low_count = 0;
    high_count = 0;
    getLow8SectionValue();
    getHigh12SectionValue();

    Serial.println("low 8 sections value = ");
    for (int i = 0; i < 8; i++)
    {
      Serial.print(low_data[i]);
      Serial.print(".");
      if (low_data[i] >= sensorvalue_min && low_data[i] <= sensorvalue_max)
      {
        low_count++;
      }
      if (low_count == 8)
      {
        Serial.print("      ");
        Serial.print("PASS");
      }
    }
    Serial.println("  ");
    Serial.println("  ");
    Serial.println("high 12 sections value = ");
    for (int i = 0; i < 12; i++)
    {
      Serial.print(high_data[i]);
      Serial.print(".");

      if (high_data[i] >= sensorvalue_min && high_data[i] <= sensorvalue_max)
      {
        high_count++;
      }
      if (high_count == 12)
      {
        Serial.print("      ");
        Serial.print("PASS");
      }
    }

    Serial.println("  ");
    Serial.println("  ");

    for (int i = 0 ; i < 8; i++) {
      if (low_data[i] > THRESHOLD) {
        touch_val |= 1 << i;

      }
    }
    for (int i = 0 ; i < 12; i++) {
      if (high_data[i] > THRESHOLD) {
        touch_val |= (uint32_t)1 << (8 + i);
      }
    }

    while (touch_val & 0x01)
    {
      trig_section++;
      touch_val >>= 1;
    }
    Serial.print("water level = ");
    Serial.print(trig_section * 5);
    Serial.println("% ");
    Serial.println(" ");
    Serial.println("*********************************************************");
    delay(1000);
  }
}



#endif