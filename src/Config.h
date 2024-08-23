#ifndef CONFIG_H
#define CONFIG_H

const int pinOffen = 13;            // mit offen und geschlossen sind die Enden des LED-Streifen gemeint
const int pinGeschlossen = 12; 

const char* ssid = "ESP32_LED";     // wird in MyWebHandler.cpp für WLAN-Hosting benötigt
const char* password = "kanyewest"; 

#endif