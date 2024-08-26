#include <Arduino.h>
#include <MyWebHandler.h>
#include <MyLEDHandler.h>
#include "Config.h"

MyLEDHandler myLEDHandler(pinOffen, pinGeschlossen);
MyWebHandler myWebHandler(myLEDHandler);          //myLEDHandler-Objekt wird an myWebHandler übergeben, sodass über den WebServer volle Kontrolle über das myWebHandler gegeben ist

void setup(){
    Serial.begin(115200);

    myWebHandler.setup(ssid, password);           //werte sind in Config.h hinterlegt
}

void loop(){
    myWebHandler.loop();
    myLEDHandler.loop();
}