#include <Arduino.h>
#include <MyWebHandler.h>
#include <MyLEDHandler.h>
#include "Config.h"

MyWebHandler myWebHandler;
MyLEDHandler myLEDHandler;

void setup(){
    Serial.begin(115200);

    myWebHandler.setup();

    myLEDHandler.setup(pinOffen, pinGeschlossen); //werte sind in Config.h definiert
}

void loop(){
    myWebHandler.loop();
}