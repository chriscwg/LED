#include "MyWebHandler.h"
#include <WiFi.h>

WiFiServer server(80);
const char* ssid = "ESP32_LED";
const char* password = "kanyewest";

void MyWebHandler::setup(){
  WiFi.softAP(ssid, password);

  Serial.print("AC: ");
  Serial.println(WiFi.softAPIP());
  Serial.print(" | ");
  Serial.println(password);

  server.begin();
}