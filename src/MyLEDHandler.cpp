#include <Arduino.h>
#include "MyLEDHandler.h"

void MyLEDHandler::setup(int pinOffen, int pinGeschlossen){
    pinMode(pinOffen, OUTPUT);
    pinMode(pinGeschlossen, OUTPUT);
}

void MyLEDHandler::test(){
    Serial.println("TEST");
}