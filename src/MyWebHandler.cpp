#include "MyWebHandler.h"
#include "WiFi.h"
#include <ArduinoJson.h>

MyWebHandler::MyWebHandler(MyLEDHandler& myLEDHandler) : _server(80), _myLEDHandler(myLEDHandler){}

void MyWebHandler::handleRoot(){
  _server.send(200, "text/html", HTML_ROOT);
}

void MyWebHandler::test(){
  _server.send(200, "text/html", "<h1>Test is being processed</h1>");
  _myLEDHandler.test();
}

void MyWebHandler::startPulseAnimation(){
  _myLEDHandler.startPulseAnimation();
  _server.send(200, "text/html", HTML_PULSE);
}

void MyWebHandler::stopAnimations(){
  _server.send(200, "text/html", HTML_ROOT);
  _myLEDHandler.stopAnimations();
}

void MyWebHandler::startWaveAnimation(){
  _server.send(200, "text/html", HTML_WAVE);
  _myLEDHandler.startWaveAnimation();
}

void MyWebHandler::startBootAnimation(){
  _server.send(200, "text/html", "<h1>BOOT</h1>");
  _myLEDHandler.startBootAnimation();
}

void MyWebHandler::updateMaxBrightness(){
  String m = "";
  if(_server.hasArg("plain")){
    m += _server.arg("plain");

    StaticJsonDocument<200> doc;  //veraltet (noch austauschen)
    DeserializationError error = deserializeJson(doc, m);

    if(error){
      Serial.println("ERROR WITH DESERIALIZATION");
      return;
    }

    String newBrightness = doc["newBrightness"];
    _myLEDHandler.setMaxBrightness(newBrightness.toInt());
  }else{
    Serial.println("ERROR: no data transmitted");
  }
  Serial.println("update Brightness called");
}

void MyWebHandler::updateAnimationSpeed(){
  if(_server.hasArg("plain")){
    StaticJsonDocument<200> doc;  //veraltet (noch austauschen)
    DeserializationError error = deserializeJson(doc, _server.arg("plain"));

    if(error){
      Serial.println("ERROR WITH DESERIALIZATION");
      return;
    }

    String newAnimationSpeed = doc["newAnimationSpeed"];
    _myLEDHandler.setAnimationSpeed(newAnimationSpeed.toInt());
  }else{
    Serial.println("ERROR: no data transmitted");
  }
  Serial.println("updateAnimationSpeed called");
}

void MyWebHandler::setup(const char* ssid,const char* password){
  //WiFi - um Handy/Laptop mit WLAN des ESPs zu verbinden -> mit ESP im gleichen Netzwerk
  WiFi.softAP(ssid, password);
  Serial.print("AC: ");
  Serial.print(WiFi.softAPIP());
  Serial.print(" | ");
  Serial.println(password);

  //WebServer - um HTTP-Anfragen zu bearbeiten
  _server.on("/", std::bind(&MyWebHandler::handleRoot, this));
  _server.on("/test", std::bind(&MyWebHandler::test, this));
  _server.on("/startPulseAnimation", std::bind(&MyWebHandler::startPulseAnimation, this));
  _server.on("/stop", std::bind(&MyWebHandler::stopAnimations, this));
  _server.on("/startWaveAnimation", std::bind(&MyWebHandler::startWaveAnimation, this));
  _server.on("/startBootAnimation", std::bind(&MyWebHandler::startBootAnimation, this));
  _server.on("/updateMaxBrightness", std::bind(&MyWebHandler::updateMaxBrightness, this));
  _server.on("/updateAnimationSpeed", std::bind(&MyWebHandler::updateAnimationSpeed, this));
  _server.begin();
};


void MyWebHandler::loop(){
  _server.handleClient();
}
