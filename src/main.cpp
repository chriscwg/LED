#include <Arduino.h>
#include <MyWebHandler.h>
#include <MyLEDHandler.h>
#include "Config.h"

void setup(){
    Serial.begin(115200);

    MyWebHandler myWebHandler;
    myWebHandler.setup();

    MyLEDHandler myLEDHandler;
    myLEDHandler.setup(pinOffen, pinGeschlossen); //werte sind in Config.h definiert
}

void loop(){
    Serial.println("Ye");
}