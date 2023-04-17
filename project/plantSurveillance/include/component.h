#ifndef _COMPONENT_H
#define _COMPONENT_H

#include <string>
#include <iostream>
using namespace std;

class component {
public: 
    //constructors
    component(){
    }
    component(string name){
        this->name = name;
    }
    component(uint8_t rpin){
        this->rpin = rpin;
    }
    component(string name, uint8_t rpin){
        this->rpin = rpin;
        this->name = name;
    }
    component(string name, uint8_t rpin, uint8_t wpin){
        this->rpin = rpin;
        this->wpin = wpin;
        this->name = name;
    }
    //constructor w wpin&rpin for actuator
    //constructor w only rpin for sensor

    //methods
    void init();

    /*
    void startSerial(){
        cout << "Starting serial monitor..." << endl;
        //Serial.begin();
    }
    */

    uint8_t getReadPin(){
        return this->rpin;
    }
    uint8_t getWritePin(){
        return this->wpin;
    }
    string getName(){
        return this->name;
    } 

//private: 
protected: //subclasses can access these attributes
    string name;
    uint8_t rpin;
    uint8_t wpin; 
};

#endif