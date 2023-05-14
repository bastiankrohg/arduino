# Planty - Automated Plant Irrigation and surveillance system
C++ project using an esp8266 

## Setup: 
To be able to run our program you need to follow these steps: 
1) Download the zipped project from our git or clone it using the following command:  
`git clone git@github.com:bastiankrohg/arduino.git`
2) Open project in the Arduino IDE (by clicking planty.ino)
3) Project dependencies: Make sure to have included the correct third-party libraries: Click on "Include Libraries" and add the following libraries: (as include .zip library or by searching and installing them with the IDE)
  * Grove - LCD RGB Backlight 1.0.0 - "rgb_lcd.h" 
  * DHT sensor library by Adafruit - "DHT.h"
  The following two zipped libraries are included in the project, in the folder libraries: 
  * Grove - Chainable LED - "ChainableLED.h" 
  * Grove - Temperature and Humidity - "DHT.h"
4) Configure target board = NodeMCU 1.0 ESP8266 and port as the port through which you have connected the esp8266 to your computer.
5) Press the "Upload" button inside the Arduino IDE

## User manual: 
Now that you have completed the setup, the project should be working if the board and its components have been wired correctly. Here is the suggested pin scheme: 
PIN_SOIL A0 (Connected using 3 wires: signal (yellow) to A0, ground (black) to GND and Vcc (purple) to 3v3)
PIN_RELAY D3
PIN_TEMP_HUMIDITY D7
PIN_STATUS_LED_CLK_PIN D8
PIN_STATUS_LED_DATA_PIN D4
PIN_BUTTON_PUMP_CTRL D6
PIN_BUZZER D9

In order for the water pump to work, it needs to be powered. This can be done by either connecting the grove adapter connected to the power supply which goes through the relay to *another* board (this is because the pump will draw too much current when activated and thus create noise and jam the other components) or to an external battery. 

When powering up the system, you will notice that after the initial setup, the system will seem to be static. This is intentional.
The functionalities of our system include: 
 * Upon activating the watering system (Water pump ON), the buzzer will make a noise to notify the plant caretaker of the plant being watered.
 * The button activates the watering system if the water reservoir level is > 10%, and the soil moisture level is not above its upper threshold (if the soil is too moist).
 * The watering is also activated if the soil moisture level is lower than its lower threshold value, meaning that the plant's soil is dry and needs water. 
 * The Water level status light, which is indicated by the sticker beneath is green as long as the status of the water level is correct. However, when the water level is too low, this light will shine red.
 * The temperature status light works with the same principle. If the temperature is either too high or too low for the plant, then the light shines red, whereas if the status is OK then the light is green.
 * The LCD screen displays important information, such as current sensor data as well as warnings and errors that the system occurs.
 * The status LEDs along with the buzzer are also used to notify the plant caretaker upon encountering problems. The alarm light is caracterized by the two status lights alternating red and blue colors.


If the button will not activate the watering system, it is due to the water level being too low and thus blocking the manual watering as priority is given to the water level being correct to avoid damaging the water pump. 

