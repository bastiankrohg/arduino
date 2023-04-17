#ifndef _DISPLAY_H
#define _DISPLAY_H

#include "actuator.h"

class display : public actuator {
public: 
    display();
    display(string name, int pin);
    
    void displayData();

private: 


};

#endif