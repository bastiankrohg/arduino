#include "../include/sensor.h"
#include <iostream>
using namespace std;

sensor::sensor(){
    this->pin = -1;
    this->name = "";
}
sensor::sensor(string name, int pin){
    this->pin = pin;
    this->name = name; 
}
void sensor::init(){
    cout << "init" << endl; 
}
string sensor::getName(){
    return this->name;
}
int sensor::getPin(){
    return this->pin;
}
