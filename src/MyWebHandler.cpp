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
  String htmlContent = HTML_PULSE;
  htmlContent.replace("{ANIMATION_SPEED_PLATZHALTER}", String(_myLEDHandler.getAnimationSpeed()));
  htmlContent.replace("{ANIMATION_INCREMENT_PLATZHALTER}", String(_myLEDHandler.getAnimationIncrement()));
  htmlContent.replace("{MAX_BRIGHTNESS_PLATZHALTER}", String(_myLEDHandler.getMaxBrightness()));
  htmlContent.replace("{PAUSE_ON_MAX_BRIGHTNESS_PLATZHALTER}", String(_myLEDHandler.getPauseOnMaxBrightness()));
  htmlContent.replace("{MIN_BRIGHTNESS_PLATZHALTER}", String(_myLEDHandler.getMinBrightness()));
  _server.send(200, "text/html", htmlContent);
}

void MyWebHandler::stopAnimations(){
  _server.send(200, "text/html", HTML_ROOT);
  _myLEDHandler.stopAnimations();
}

void MyWebHandler::startWaveAnimation(){
  String htmlContent = HTML_WAVE;
  htmlContent.replace("{ANIMATION_SPEED_PLATZHALTER}", String(_myLEDHandler.getAnimationSpeed()));
  htmlContent.replace("{ANIMATION_INCREMENT_PLATZHALTER}", String(_myLEDHandler.getAnimationIncrement()));
  htmlContent.replace("{MAX_BRIGHTNESS_PLATZHALTER}", String(_myLEDHandler.getMaxBrightness()));
  htmlContent.replace("{MIN_BRIGHTNESS_PLATZHALTER}", String(_myLEDHandler.getMinBrightness()));
  htmlContent.replace("{PAUSE_ON_MAX_BRIGHTNESS_PLATZHALTER}", String(_myLEDHandler.getPauseOnMaxBrightness()));
  _server.send(200, "text/html", htmlContent);
  _myLEDHandler.startWaveAnimation();
}

void MyWebHandler::startBootAnimation(){
  _server.send(200, "text/html", HTML_BOOT);
  _myLEDHandler.startBootAnimation();
}

void MyWebHandler::updateMaxBrightness(){
  if(_server.hasArg("plain")){
    StaticJsonDocument<200> doc;  //veraltet (noch austauschen)
    DeserializationError error = deserializeJson(doc, _server.arg("plain"));

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

void MyWebHandler::setAnimationIncrement(){
  if(_server.hasArg("plain")){
    StaticJsonDocument<200> doc;  //veraltet (noch austauschen)
    DeserializationError error = deserializeJson(doc, _server.arg("plain"));

    if(error){
      Serial.println("ERROR WITH DESERIALIZATION");
      return;
    }

    String newAnimationIncrement = doc["newAnimationIncrement"];
    Serial.println(newAnimationIncrement);
    _myLEDHandler.setAnimationIncrement(newAnimationIncrement.toInt());
  }else{
    Serial.println("ERROR: no data transmitted");
  }
  Serial.println("updateAnimationSpeed called");
}

void MyWebHandler::setPauseOnMaxBrightness(){
  if(_server.hasArg("plain")){
    StaticJsonDocument<200> doc;  //veraltet (noch austauschen)
    DeserializationError error = deserializeJson(doc, _server.arg("plain"));

    if(error){
      Serial.println("ERROR WITH DESERIALIZATION");
      return;
    }

    String newPauseOnMaxBrightness = doc["newPauseOnMaxBrightness"];
    Serial.println(newPauseOnMaxBrightness);
    _myLEDHandler.setPauseOnMaxBrightness(newPauseOnMaxBrightness.toInt());
  }else{
    Serial.println("ERROR: no data transmitted");
  }
  Serial.println("updateAnimationSpeed called");
}

void MyWebHandler::setMinBrightness(){
  if(_server.hasArg("plain")){
    StaticJsonDocument<200> doc;  //veraltet (noch austauschen)
    DeserializationError error = deserializeJson(doc, _server.arg("plain"));

    if(error){
      Serial.println("ERROR WITH DESERIALIZATION");
      return;
    }

    String newMinBrightness = doc["newMinBrightness"];
    Serial.println(newMinBrightness);
    _myLEDHandler.setMinBrightness(newMinBrightness.toInt());
  }else{
    Serial.println("ERROR: no data transmitted");
  }
  Serial.println("updateAnimationSpeed called");
}

void MyWebHandler::startWaveAnimation2(){
  _myLEDHandler.startWaveAnimation2();
  String htmlContent = HTML_WAVE2;
  htmlContent.replace("{ANIMATION_SPEED_PLATZHALTER}", String(_myLEDHandler.getAnimationSpeed()));
  htmlContent.replace("{ANIMATION_INCREMENT_PLATZHALTER}", String(_myLEDHandler.getAnimationIncrement()));
  htmlContent.replace("{MAX_BRIGHTNESS_PLATZHALTER}", String(_myLEDHandler.getMaxBrightness()));
  htmlContent.replace("{MIN_BRIGHTNESS_PLATZHALTER}", String(_myLEDHandler.getMinBrightness()));
  htmlContent.replace("{OFFSET_PLATZHALTER}", String(_myLEDHandler.getOffsetWave2()));
  _server.send(200, "text/html", htmlContent);
}

void MyWebHandler::setOffsetWave2(){
  if(_server.hasArg("plain")){
    StaticJsonDocument<200> doc;  //veraltet (noch austauschen)
    DeserializationError error = deserializeJson(doc, _server.arg("plain"));

    if(error){
      Serial.println("ERROR WITH DESERIALIZATION");
      return;
    }

    String newOffset = doc["newOffset"];
    Serial.println(newOffset);
    _myLEDHandler.setOffsetWave2(newOffset.toInt());
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
  _server.on("/setAnimationIncrement", std::bind(&MyWebHandler::setAnimationIncrement, this));
  _server.on("/setPauseOnMaxBrightness", std::bind(&MyWebHandler::setPauseOnMaxBrightness, this));
  _server.on("/setMinBrightness", std::bind(&MyWebHandler::setMinBrightness, this));
  _server.on("/startWaveAnimation2", std::bind(&MyWebHandler::startWaveAnimation2, this));
  _server.on("/setOffsetWave2", std::bind(&MyWebHandler::setOffsetWave2, this));
  _server.on("/startWaveAnimation3", std::bind(&MyWebHandler::startWaveAnimation3, this));
  _server.begin();
};

void MyWebHandler::startWaveAnimation3(){
  _server.send(200, "text/html", HTML_WAVE3);
  _myLEDHandler.startWaveAnimation3();
}


void MyWebHandler::loop(){
  _server.handleClient();
}
