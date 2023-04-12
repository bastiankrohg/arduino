#ifndef _SENSOR_H
#define _SENSOR_H

#include <string>
using namespace std; 

class sensor{
public: 
    //constructor
    sensor();
    sensor(string name, int pin);

    //methods
    void init();
    int getPin();
    string getName(); 

private:
    //attributes
    string name;
    int pin;
};




#endif