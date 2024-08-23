#include <Arduino.h>
#include <MyWebHandler.h>
#include <MyLEDHandler.h>
#include "Config.h"

MyWebHandler myWebHandler;
MyLEDHandler myLEDHandler;

void setup(){
    Serial.begin(115200);

    myWebHandler.setup(ssid, password);           //werte sind in Config.h hinterlegt

    myLEDHandler.setup(pinOffen, pinGeschlossen); //werte sind in Config.h hinterlegt
}

void loop(){
    myWebHandler.loop();
}