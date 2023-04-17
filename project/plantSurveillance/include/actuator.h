#ifndef _ACTUATOR_H
#define _ACTUATOR_H

#include <string>
#include <iostream>
using namespace std; 

class actuator{
public: 
    //constructor
    actuator();
    actuator(string name, int pin);

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