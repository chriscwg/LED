#include "MyWebHandler.h"
#include "WiFi.h"

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
  _server.begin();
};


void MyWebHandler::loop(){
  _server.handleClient();
}
