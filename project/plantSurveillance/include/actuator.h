#ifndef _ACTUATOR_H
#define _ACTUATOR_H

#include <string>
#include <iostream>
using namespace std; 

class actuator{
public: 
    //constructor
    actuator(){
        this->pin = -1;
        this->name = "";
    }
    actuator(string name, int pin){
        this->pin = pin;
        this->name = name;
    }

    //methods
    void init();
    int getPin(){
        return this->pin; 
    }
    string getName(){
        return this->name;
    }

private: 
    //attributes
    string name; 
    int pin; 
};

#endif