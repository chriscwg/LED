#include <Arduino.h>
#include <MyWebHandler.h>

void setup(){
    Serial.begin(115200);

    MyWebHandler myWebHandler;
    myWebHandler.setup();
}

void loop(){
    Serial.println("Ye");
}