#include "MyWebHandler.h"
#include "WiFi.h"

const char* ssid = "ESP32_LED";     //zu Config.h noch verschieben
const char* password = "kanyewest"; 

MyWebHandler::MyWebHandler() : _server(80) {}

void MyWebHandler::handleRoot(){
  _server.send(200, "text/html", "<h1>Ye</h1>");
}

void MyWebHandler::setup(){
  WiFi.softAP(ssid, password);

  Serial.print("AC: ");
  Serial.print(WiFi.softAPIP());
  Serial.print(" | ");
  Serial.println(password);

  _server.on("/", std::bind(&MyWebHandler::handleRoot, this));

  _server.begin();
};


void MyWebHandler::loop(){
  _server.handleClient();
}
