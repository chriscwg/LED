#include "MyWebHandler.h"
#include "WiFi.h"

MyWebHandler::MyWebHandler(MyLEDHandler& myLEDHandler) : _server(80), _myLEDHandler(myLEDHandler){}

void MyWebHandler::handleRoot(){
  _server.send(200, "text/html", "<h1>Ye</h1>");
}

void MyWebHandler::test(){
  _server.send(200, "text/html", "<h1>Test is being processed</h1>");
  _myLEDHandler.test();
}

void MyWebHandler::setup(const char* ssid,const char* password){
  WiFi.softAP(ssid, password);

  Serial.print("AC: ");
  Serial.print(WiFi.softAPIP());
  Serial.print(" | ");
  Serial.println(password);

  _server.on("/", std::bind(&MyWebHandler::handleRoot, this));
  _server.on("/test", std::bind(&MyWebHandler::test, this));

  _server.begin();
};


void MyWebHandler::loop(){
  _server.handleClient();
}
