#include "MyWebHandler.h"
#include "WiFi.h"

const char* ssid = "ESP32_LED";     //zu Config.h noch verschieben
const char* password = "kanyewest"; 

void MyWebHandler::setup(){
  WiFi.softAP(ssid, password);

  Serial.print("AC: ");
  Serial.println(WiFi.softAPIP());
  Serial.print(" | ");
  Serial.println(password);
};