/*****************************************************
Pauline DUPUY and Bastian KROHG
4th year INSA Toulouse AE Embedded Systems

C++ Arduino project - Automated / connected greenhouse

  Operational status of system components:
    Exceptions:                                   Not yet implemented
    Use of STL Data Structures:               Not yet implemented
    Operator redefinition:                        Not yet implemented
    Iterators:                                    Not yet implemented

    Sensors: 
      * Soil moisture sensor:                     OK!
      * Water Level indicator:                    PROBLEM: Sometimes the reading is stuck at last value 
      * Temperature & Humidity sensor:            TEMP: OK; HUMID: READING ONLY 0
    Actuators:
      * LCD Screen:                               Missing display message creation + autoscroll
      * Water Pump + Relay:                       OK!
      * Buzzer:                                   Not yet tested
      * Button:                                   OK!
      * LED Chain:                                OK, but problem when written as a class (problem with constructor)
        * Status/Warning lights:                  OK!
          * Temperature too high or too low => Temp light red, else green
          * Water level too low (<10%) => Water lvl light red, else green
    Functionalities:
      Water level low control block:        OK
        * if water level too low, activate alarm and block watering functionality
        * if soil moisture too low, activate watering until moisture level normalized
        * if button pushed, manually activate watering 
          (priority is given to the water level indicator => doesn't work if water level is too low)
      Error messages:                           Not yet implemented
      Warning messages:                         OK, but not yet displayed/treated
      Plant caretaker info messages by email:   Not yet implemented
*****************************************************/

/**Pinout.h contains the project's pin layout, macros and more**********************/
#include "Pinout.h"

/**SETUP********************************************************************************/
void setup() {
  //initialize LED chain
  ledSetupColorCycle();

  //Waterpump / relay
  pinMode(PIN_RELAY, OUTPUT);
  //Button is configured as input in Button.h
  pinMode(PIN_BUTTON_PUMP_CTRL, INPUT);

  //keep pump off by default
  digitalWrite(PIN_RELAY,LOW);
  //buzzer off by default
  buzzer.off();
  //lcd
  lcd.begin(16, 2);
  // Print a message to the LCD.
  lcd.print("I'm thirsty!");
  Serial.begin(9600);
}

/**MAIN********************************************************************************/
void loop() {
  // put your main code here, to run repeatedly:
  delay(1);

  /**CHECK STATES TO UPDATE WARNING LIGHTS***********************************/
  /**Temperature**/
  if (!temperatureSensor.temperatureStatusOK()){
    setWarningLightTemp();
    temperatureWarning = true;
    warning_message += " TEMPERATURE ";
  } else {
    setNormalStateTempLight();
  }
  delay(1);
  
  /**Humidity**/
  
  if (!humiditySensor.humidityStatusOK()){
    warning_message += " HUMIDITY "; 
    humidityWarning = true;
  } else {
    //
  }
  delay(1);
  
  /**Soil Moisture**/
  if (!soilMoisture.soilMoistureOK()){
    //setWarningLightSoil();
    warning_message += " SOIL ";
    soilWarning = true;
  } else {
    //setNormalStateSoilLight();
  }
  delay(1);
  
  
  /**Water level**/
  if (!waterlevelSensor.waterlevelOK()) {
    setWarningLightWaterlevel();
    warning_message += " WATER LVL ";
    waterlevelLow = true;
  } else {
    setNormalStateWaterlevelLight();
    waterlevelLow = false;
  }
  delay(1);
  

  /**CREATE DISPLAY MESSAGE WITH SENSOR INFORMATION***********************************/
  displaymessage = createDisplayMessage();
  //lcd.print(displaymessage); //need to activate autoscroll
  Serial.println(displaymessage);
  
  buttonState = digitalRead(PIN_BUTTON_PUMP_CTRL);
  //buttonState = buttonPumpCtrl.readButton();
  //buttonPumpCtrl.isButtonPressed();
  
  Serial.println(buttonState);
  //debug_print_in_serial();


  /**WATER PUMP CONTROL STRUCTURE*****************************************************/
    /*waterlevelSensor.waterlevelOK() &&*/
  /*if (waterlevelLow){
    //Serial.println("True");
  } else {
    //Serial.println("False");
  }*/
  delay(1);
  

  if (!waterlevelLow && !soilMoisture.soilMoistureHigh() && (buttonState || soilMoisture.soilMoistureLow())){
    waterpump.on();
    lcd.display();
    buzzer.buzz();
  } else {
    //waterpump.activateIrrigationSystem2s();
    waterpump.off();
    lcd.noDisplay();
  }
  delay(50);

  //TODO
    //Display message on lcd screen with autoscroll
    //if temperature too high, notify caretaker --> By msg / email?             => NOT YET
  
}
