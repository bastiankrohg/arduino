#ifndef _DISPLAY_H
#define _DISPLAY_H

#include "rgb_lcd.h"
#include "string.h"
#include "Actuator.h"

class Display : public Actuator{
  public:
    Display() : Actuator{}{
    }

    Display(uint8_t rpin) : Actuator {rpin} {
    }

    Display(string name, uint8_t rpin) : Actuator{name,rpin}{
    }

    Display(rgb_lcd LCD) : Actuator{}{
      this->lcd = LCD; 
    }

    ~Display() {} 


    void startScreen(int rows, int col);
    void displayData(String data);
    void display();
    void clearDisplay();


    void activateAutoscroll();

    rgb_lcd lcd;

  protected: //or friend
    void init() const;
    void updateData(String newData);



  private:
    int pin;
    String latestData;
};

#endif