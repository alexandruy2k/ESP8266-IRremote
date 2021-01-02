# ESP8266-IRremote

This is the first implementation of an infrared remote control gateway using a cheap ESP8266 board and an IR LED

The full implementation in my home consists of an ESP8266 plus some minimal circuitry connected to my WiFi network, together 
with a SmartThings Hub and a Google Home Device I am able to automate the devices in my living room.
One of the coolest features I have implemented is a movie mode triggered either by a voice command or a single button press which
configures my lights, closes the curtains, turns on my zigbee sockets and finally turns on my projector, surround sound, 
HDMI switch and Smart TV Box. This saves me having to manually do this and work with 4 different remotes

The ESP8266 is set up as a web server and it listens to HTTP POST requests.
These requests can be generated using curl, an online form generator or as I personally use it with a custom DTH for my
Samsung SmartThings hub.
The DTH can be found in this repo https://github.com/alexandruy2k/Smartthings/tree/master/devicetypes/abuda

using IRremoteESP8266 version=2.7.6 and for the hardware using a Nodemcu board with a ESP-12F module on board

Arduino IDE configured to use NodeMCU 1.0 Board with buildin led 16, upload speed 115200, 80MHz CPU and 4MB flash size
