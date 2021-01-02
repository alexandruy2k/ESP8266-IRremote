/*
 * ESP8266 IR remote based on IRremoteESP8266: IRServer example
 * 
 * V0.1 - basic implementation working with minimal security
 * TODO: add TLS encryption which will make it more secure but not prevent anyone that knows
 * my IP to abuse the server
 * TODO: add secure API authentication token
 */
 
#include <Arduino.h>
#include <ESP8266WiFi.h>
#include <ESP8266WebServer.h>
#include <ESP8266mDNS.h>
#include <IRsend.h>
#include <WiFiClient.h>
#include "constants.h"

MDNSResponder mdns;
ESP8266WebServer server(80);

IRsend irsend(kIrLed);  // Set the GPIO to be used to sending the message.

void handleRoot() {
  server.send(200, "text/html", "none");
}

void handleTurnOn() {
  digitalWrite(led, 0);
  if (server.method() == HTTP_POST) {
    server.send(200, "text/plain", "Rejected\n");
    String message = "turnon POST Body was:\n";
    for (uint8_t i = 0; i < server.args(); i++) {
      message += " " + server.argName(i) + ": " + server.arg(i) + "\n";
    }
    Serial.println(message);
    
    String cmd = server.arg(0);
    if (isMediaCenter(cmd)) {
      Serial.println("IR: Turning Media Center ON");
      irsend.sendNEC(QPlusOnOff, 32, 10);
      irsend.sendNEC(OptomaHd65OnOff, 32, 10);
      irsend.sendSAMSUNG(LgOpticalChannel, 32, 0);
    }
    else if (isProjector(cmd)) {
      Serial.println("IR: Turning Projector ON");
      irsend.sendNEC(OptomaHd65OnOff, 32, 10);
    }
    else if (isSoundSystem(cmd)) {
      Serial.println("IR: Turning surround system ON");
      irsend.sendSAMSUNG(LgOpticalChannel, 32, 0);
      
    }
    else if (isAndroidBox(cmd)) {
      Serial.println("IR: Turning Android Box ON");
      irsend.sendNEC(QPlusOnOff, 32, 10);
    }
    else if (isHdmiChannel1(cmd)) {
      Serial.println("IR: Changing HDMI Channel1");
      irsend.sendNEC(HdmiChannel1, 32, 0);
    }
    else if (isHdmiChannel2(cmd)) {
      Serial.println("IR: Changing HDMI Channel2");
      irsend.sendNEC(HdmiChannel2, 32, 0);
    }
    else if (isHdmiChannel3(cmd)) {
      Serial.println("IR: Changing HDMI Channel3");
      irsend.sendNEC(HdmiChannel3, 32, 0);
    }
    else {
      Serial.println("Command not understood");
    }
  }
  else {
    Serial.println(server.method());
  }
  digitalWrite(led, 1);
}

void handleTurnOff() {
  digitalWrite(led, 0);
  if (server.method() == HTTP_POST) {
    server.send(200, "text/plain", "Rejected\n");
    String message = "turnoff POST Body was:\n";
    for (uint8_t i = 0; i < server.args(); i++) {
      message += " " + server.argName(i) + ": " + server.arg(i) + "\n";
    }
    Serial.println(message);
    
    String cmd = server.arg(0);
    if (isMediaCenter(cmd)) {
      Serial.println("IR: Turning Media Center OFF");
      irsend.sendNEC(OptomaHd65OnOff, 32, 10);
      irsend.sendNEC(QPlusOnOff, 32, 10);
      irsend.sendSAMSUNG(LgOnOff, 32, 0);
      irsend.sendNEC(OptomaHd65OnOff, 32, 10);
    }
    else if (isProjector(cmd)) {
      Serial.println("IR: Turning TV OFF");
      irsend.sendNEC(OptomaHd65OnOff, 32, 10);
      delay(3000);
      irsend.sendNEC(OptomaHd65OnOff, 32, 10);
    }
    else if (isSoundSystem(cmd)) {
      Serial.println("IR: Turning surround system OFF");
      irsend.sendSAMSUNG(LgOnOff, 32, 0);
    }
    else if (isAndroidBox(cmd)) {
      Serial.println("IR: Turning Android Box OFF");
      irsend.sendNEC(QPlusOnOff, 32, 10);
    }
  }
  digitalWrite(led, 1);
}

void handleVolume() {
  digitalWrite(led, 0);
  if (server.method() == HTTP_POST) {
    server.send(200, "text/plain", "Rejected\n");
    String message = "volume POST Body was:\n";
    for (uint8_t i = 0; i < server.args(); i++) {
      message += " " + server.argName(i) + ": " + server.arg(i) + "\n";
    }
    Serial.println(message);
    
    String cmd = server.arg(0);
    if (cmd.equalsIgnoreCase("up")) {
      Serial.println("IR: Volue UP");
      irsend.sendSAMSUNG(LgVolumeUp, 32, 2);
    }
    else if (cmd.equalsIgnoreCase("down")) {
      Serial.println("IR: Volue down");
      irsend.sendSAMSUNG(LgVolumeDown, 32, 2);
    }
    else if (cmd.equalsIgnoreCase("optical")) {
      Serial.println("IR: Optical Channel");
      irsend.sendSAMSUNG(LgOpticalChannel, 32, 0);
    }
  }
  digitalWrite(led, 1);
}

void handleNotFound() {
  // don't return standard file not found message.
  // This makes this a little bit more secure as hackers should be able to easily bruteforce
  // through the server and find the valid URLs. If hackers are aware that I don't reply
  // to incorrect URLs they will still be able to bruteforce
  // however as the source code is on github anyone that is aware of this code already knows
  // the valid URLs to use
  String message = "File Not Found\n\n";
  message += "URI: ";
  message += server.uri();
  message += "\nMethod: ";
  message += (server.method() == HTTP_GET)?"GET":"POST";
  message += "\nArguments: ";
  message += server.args();
  message += "\n";
  for (uint8_t i = 0; i < server.args(); i++)
    message += " " + server.argName(i) + ": " + server.arg(i) + "\n";
  Serial.println(message);
  return;
  server.send(404, "text/plain", message);
}

bool isMediaCenter(String cmd) {
  if (cmd.equalsIgnoreCase("media center") || cmd.equalsIgnoreCase("media centre") || cmd.equalsIgnoreCase("media system")){
    return true;
  }
  else {
    return false;
  }
}

bool isProjector(String cmd) {
  if (cmd.equalsIgnoreCase("tv") || cmd.equalsIgnoreCase("projector")){
    return true;
  }
  else {
    return false;
  }
}

bool isSoundSystem(String cmd) {
  if (cmd.equalsIgnoreCase("surround system") || cmd.equalsIgnoreCase("speakers") || cmd.equalsIgnoreCase("sound") || cmd.equalsIgnoreCase("surround sound") || cmd.equalsIgnoreCase("sound system")){
    return true;
  }
  else {
    return false;
  }
}

bool isAndroidBox(String cmd) {
  if (cmd.equalsIgnoreCase("android box") || cmd.equalsIgnoreCase("tv box") || cmd.equalsIgnoreCase("android tv")){
    return true;
  }
  else {
    return false;
  }
}

bool isHdmiChannel1(String cmd) {
  if (cmd.equalsIgnoreCase("channel chromecast") || cmd.equalsIgnoreCase("channel one") || cmd.equalsIgnoreCase("channel 1")){
    return true;
  }
  else {
    return false;
  }
}

bool isHdmiChannel2(String cmd) {
  if (cmd.equalsIgnoreCase("channel android box") || cmd.equalsIgnoreCase("channel tv box") || cmd.equalsIgnoreCase("channel android tv") || cmd.equalsIgnoreCase("channel two") || cmd.equalsIgnoreCase("channel 2")){
    return true;
  }
  else {
    return false;
  }
}

bool isHdmiChannel3(String cmd) {
  if (cmd.equalsIgnoreCase("channel three") || cmd.equalsIgnoreCase("channel 3")){
    return true;
  }
  else {
    return false;
  }
}

void setup(void) {
  irsend.begin();
  pinMode(led, OUTPUT);
  digitalWrite(led, 1);
  Serial.begin(115200);
  WiFi.begin(ssid, password);
  Serial.println("");

  // Wait for connection
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }
  Serial.println("");
  Serial.print("Connected to ");
  Serial.println(ssid);
  Serial.print("IP address: ");
  Serial.println(WiFi.localIP());

  if (mdns.begin("esp8266", WiFi.localIP())) {
    Serial.println("MDNS responder started");
  }

  server.on("/turnon", handleTurnOn);
  server.on("/turnoff", handleTurnOff);
  server.on("/volume", handleVolume);
  server.onNotFound(handleNotFound);

  server.begin();
  Serial.println("HTTP server started");
}

void loop(void) {
  server.handleClient();
  mdns.update();
}
