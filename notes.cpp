  
  SETUP

    // put your setup code here, to run once:
  Serial.begin(9600);
  lcd.begin(16,2);
  //display.lcd.begin(16,2);

  //pin config
  //pinMode(pinButton, INPUT);
  pinMode(LED_BUILTIN, OUTPUT);
  pinMode(pinWPump, OUTPUT);
  //display.displayData("Setup Complete");
  //delay(1000);

  //temp sensor test
  debug.begin(115200);
  debug.println("DHTxx test!");
  Wire.begin();
  dht.begin();

  
  
  
  MAIN
  
  
  
  // put your main code here, to run repeatedly:
  //Read sensors to obtain new data, store temporarily
  /********************************/

  //Create Display message for lcd screen
  /********************************/

  //Display message
  /********************************/



  //Actions:
  //if water level too low, activate alarm and block watering functionality

  //if temperature too high, notify caretaker --> By msg / email? 

  //if soil moisture too low, activate water until moisture level normalized

  //if button pushed, override alerts to activate waterpump
      //should this work even though water level is too low???

  






  //display.displayData("Hello World!");
  //delay(1000);
  /*
  Serial.print("Light sensor value: ");
  Serial.println(lightSensor.readAnalogLightSensor());
  Serial.println();
  */

  delay(1000);
  Serial.print("Temperature and humidity value: ");
  //popo
  Serial.println();

  delay(1000);
  
  Serial.print("Soil moisture value: ");
  //popo
  Serial.println();
  delay(1000);

  //if button pressed, light switches on or off
  if(buttonLED.isButtonPressed()) {
    isOverheadLightOn = !isOverheadLightOn;

    Serial.print("LED Status: ");
    Serial.println(isOverheadLightOn);
    yield();

    //LED On/Off
    toggleLED(isOverheadLightOn, led);
  }
  
  delay(1);

  if (buttonPump.isButtonPressed()){
    Serial.println("Water pump activated");
    while (buttonPump.isButtonPressed()){
    //activate pump
    /*******************/
    //activate buzzer
    /*****************/
    //update watchdog
    delay(1);
    }
  }

  delay(1);

  if (soilMoisture.readSoilSensorValue() <= soilThreshold) {
    while (soilMoisture.readSoilSensorValue() <= soilThreshold) {
      //activate pump
      /******************/

      //activate buzzer
      /*****************/

      //update watchdog
      delay(1);
    }
  }
  float temp_hum_val[2] = {0};
  // Reading temperature or humidity takes about 250 milliseconds!
  // Sensor readings may also be up to 2 seconds 'old' (its a very slow sensor)


  if (!dht.readTempAndHumidity(temp_hum_val)) {
      debug.print("Humidity: ");
      debug.print(temp_hum_val[0]);
      debug.print(" %\t");
      debug.print("Temperature: ");
      debug.print(temp_hum_val[1]);
      debug.println(" *C");
  } else {
      debug.println("Failed to get temperature and humidity value.");
  }

  waterpump.activateIrrigationSystem2s();
  

  //delay(1500);

  
  delay(1000);
  //display.clearDisplay();