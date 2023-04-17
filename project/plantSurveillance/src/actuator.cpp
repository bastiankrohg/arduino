#include "../include/actuator.h"

using namespace std;

actuator::actuator(){
    this->pin = -1;
    this->name = "";
}
actuator::actuator(string name, int pin){
    this->pin = pin;
    this->name = name; 
}
void actuator::init(){
    cout << "init" << endl; 
}
string actuator::getName(){
    return this->name;
}
int actuator::getPin(){
    return this->pin;
}
