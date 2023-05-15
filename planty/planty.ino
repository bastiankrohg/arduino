/*****************************************************
Pauline DUPUY and Bastian KROHG
4th year INSA Toulouse AE Embedded Systems

C++ Arduino project - Automated / connected greenhouse

  Operational status of system components:
    Exceptions:                                   OK! BUT not yet tested
      * Throws an exception if any of the conditions blocking the watering functionality are true
        * Throw function can be found in Pinout.h (testBeforePumpOn()), and the try is implemented in the loop() below.
    Use of STL Data Structures:                   OK! BUT needs to be tested on system
      * std::vector to store references to display message information
    Operator redefinition:                        Not yet implemented
      * 
    Iterators:                                    OK
      * Iterate over String pointers in vector that stores display information            
    Sensors: 
      * Soil moisture sensor:                     OK!
      * Water Level indicator:                    PROBLEM: Sometimes the reading is stuck at last value 
      * Temperature & Humidity sensor:            TEMP: OK; HUMID: READING ONLY 0
    Actuators:
      * LCD Screen:                               MAYBE OK! Missing autoscroll, and problem with class Display
      * Water Pump + Relay:                       OK!
      * Buzzer:                                   OK! BUT not yet tested
      * Button:                                   OK!
      * LED Chain:                                OK! BUT problem when written as a class (problem with constructor)
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
  lcd.print("***Planty***");
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
    warning_message += " W_TEMPERATURE ";
  } else {
    setNormalStateTempLight();
  }
  delay(1);
  
  /**Humidity**/
  
  if (!humiditySensor.humidityStatusOK()){
    warning_message += " W_HUMIDITY "; 
    humidityWarning = true;
  } else {
    //
  }
  delay(1);
  
  /**Soil Moisture**/
  if (!soilMoisture.soilMoistureOK()){
    //setWarningLightSoil();
    warning_message += " W_SOIL ";
    soilWarning = true;
  } else {
    //setNormalStateSoilLight();
  }
  delay(1);
  
  
  /**Water level**/
  if (!waterlevelSensor.waterlevelOK()) {
    setWarningLightWaterlevel();
    warning_message += " W_WATERLVL ";
    waterlevelLow = true;
  } else {
    setNormalStateWaterlevelLight();
    waterlevelLow = false;
  }
  delay(1);
  

  /**CREATE DISPLAY MESSAGE WITH SENSOR INFORMATION***********************************/
  //displaymessage = createDisplayMessage();
  //lcd.print(displaymessage); //need to activate autoscroll
  //Serial.println(displaymessage);
  
  //Create message with relevant sensor information and displays on screen and in serial monitor
  //!!! Blocks for MESSAGE_DELAY seconds minimum per now
  displayStringVector();

  buttonState = digitalRead(PIN_BUTTON_PUMP_CTRL);
  //buttonState = buttonPumpCtrl.readButton();
  //buttonPumpCtrl.isButtonPressed();
  
  //Serial.println(buttonState);
  //debug_print_in_serial();

  delay(1);
  if (buttonState) {
    try {
      testBeforePumpOn();
      Serial.println("Watering plant...");
      waterpump.on();
    } catch (const char *msg) {
      error_message += msg;
      cerr << msg << endl;
      Serial.println(msg);
    }
  }
  
  /* NEED TO TEST IF NEW BLOCK WORKS
  if (!waterlevelLow && !soilMoisture.soilMoistureHigh() && (buttonState || soilMoisture.soilMoistureLow())){
    waterpump.on();
    lcd.display();
    buzzer.buzz();
  } else {
    //waterpump.activateIrrigationSystem2s();
    waterpump.off();
    lcd.noDisplay();
  }
  */
  delay(50);
  

  //TODO
    //Display message on lcd screen with autoscroll
    //if temperature too high, notify caretaker --> By msg / email?             => NOT YET
  
}
