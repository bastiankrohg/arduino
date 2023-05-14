#include "Display.h"

void Display::startScreen(int rows, int col){
  this->lcd.begin(rows,col);
}

void Display::updateData(String newData){
  this->latestData = newData;
}

void Display::displayData(String data){
  this->lcd.print(data);
}

void Display::display(){
  Display::displayData(this->latestData);
}

void Display::activateAutoscroll(){
  //need to set cursors and loop?
  this->lcd.autoscroll();
}

void Display::clearDisplay(){
  this->lcd.clear();
}