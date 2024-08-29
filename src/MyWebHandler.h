#ifndef MYWEBHANDLER_H
#define MYWEBHANDLER_H

#include "WebServer.h"
#include "MyLEDHandler.h"

class MyWebHandler {
    public:
        MyWebHandler(MyLEDHandler& myLEDHandler);           //& zeichen bedeutet Referenz -> keine Kopie wird übergeben, sondern das Objekt (myLEDHandler) selbst
        void setup(const char* ssid, const char* password);
        void loop();
    private:
        void handleRoot();
        void test();
        void startPulseAnimation();
        void startWaveAnimation();
        void startBootAnimation();
        void stopAnimations();
        void updateMaxBrightness();
        void updateAnimationSpeed();
        void setAnimationIncrement();

        WebServer _server;
        MyLEDHandler _myLEDHandler;


        String JAVASCRIPT_UPDATE_MAX_BRIGHTNESS_FUNCTION =
        "   function updateMaxBrightness(value){\n"
        "       document.getElementById('maxBrightnessP').textContent = value.toString()\n"
        "       fetch('http://192.168.4.1/updateMaxBrightness', {\n"
        "           method: 'POST',\n"
        "           headers: {\n"
        "                'Content-Type': 'application/json'\n"
        "           },\n"
        "           body: JSON.stringify({ newBrightness: value })\n"
        "       })\n"
        "       .then(response => response.json())\n"
        "       .then(data => console.log(data))\n"
        "       .catch(error => console.error('Error:', error));\n"
        "   }\n";

        String JAVASCRIPT_UPDATE_ANIMATION_SPEED_FUNCTION = 
        "   function updateAnimationSpeed(value){\n"
        "       document.getElementById('animationSpeedP').textContent = 'Gesamtdauer:' +(value * 512 * 0.000001).toString() + 'sek. (' +value.toString()+')'\n"
        "       fetch('http://192.168.4.1/updateAnimationSpeed', {\n"
        "           method: 'POST',\n"
        "           headers: {\n"
        "                'Content-Type': 'application/json'\n"
        "           },\n"
        "           body: JSON.stringify({ newAnimationSpeed: value })\n"
        "       })\n"
        "       .then(response => response.json())\n"
        "       .then(data => console.log(data))\n"
        "       .catch(error => console.error('Error:', error));\n"
        "   }\n";

        String HTML_UPDATE_ANIMATION_SPEED = 
        "    <input type=\"range\" min=\"1250\" max=\"10000\" value=\"{ANIMATION_SPEED_PLATZHALTER}\" id=\"animationSpeed\" onchange=\"updateAnimationSpeed(this.value)\">\n"
        "    <p id=\"animationSpeedP\"></p>\n";

        String HTML_UPDATE_MAX_BRIGHTNESS = 
        "    <p>Helligkeit</p>\n"
        "    <input type=\"range\" min=\"0\" max=\"255\" value=\"{MAX_BRIGHTNESS_PLATZHALTER}\" id=\"maxBrightness\" onchange=\"updateMaxBrightness(this.value)\">\n"
        "    <p id=\"maxBrightnessP\">{MAX_BRIGHTNESS_PLATZHALTER}</p>\n";

        String JAVASCRIPT_SET_ANIMATION_INCREMENT =
        "   function setAnimationIncrement(value){\n"
        "       document.getElementById('animationIncrementP').textContent = value.toString(); \n"
        "       fetch('http://192.168.4.1/setAnimationIncrement', {\n"
        "           method: 'POST',\n"
        "           headers: {\n"
        "                'Content-Type': 'application/json'\n"
        "           },\n"
        "           body: JSON.stringify({ newAnimationIncrement: value })\n"
        "       })\n"
        "       .then(response => response.json())\n"
        "       .then(data => console.log(data))\n"
        "       .catch(error => console.error('Error:', error));\n"
        "   }\n";

        String HTML_ANIMATION_INCREMENT =
        "   <button onclick='setAnimationIncrement(1)'>x1</button>\n"
        "   <button onclick='setAnimationIncrement(2)'>x2</button>\n"
        "   <button onclick='setAnimationIncrement(3)'>x3</button>\n"
        "   <p id=\"animationIncrementP\">{ANIMATION_INCREMENT_PLATZHALTER}</p>\n";

        const char HTML_ROOT[888] = 
        "<!DOCTYPE html>\n"
        "<html lang=\"de\">\n"
        "<head>\n"
        "    <meta charset=\"UTF-8\">\n"
        "    <meta name=\"viewport\" content=\"width=device-width, initial-scale=1.0\">\n"
        "    <title>Document</title>\n"
        "</head>\n"
        "<body>\n"
        "    <center><h1>LED Steuerung</h1></center>\n"
        "    <h2>Pulse-Labor</h2>\n"
        "    <a href=\"/startPulseAnimation\">start</a>\n"
        "    <h2>Wave-Labor</h2>\n"
        "    <a href=\"/startWaveAnimation\">start</a>\n"
        "    <h2>BOOT</h2>\n"
        "    <a href=\"/startBootAnimation\">start</a>\n"
        "</body>\n"
        "</html>\n";

        const char HTML_BOOT[888] = 
        "<!DOCTYPE html>\n"
        "<html lang=\"de\">\n"
        "<head>\n"
        "    <meta charset=\"UTF-8\">\n"
        "    <meta name=\"viewport\" content=\"width=device-width, initial-scale=1.0\">\n"
        "    <title>Document</title>\n"
        "</head>\n"
        "<body>\n"
        "    <center><h1>BOOT</h1></center>\n"
        "    <a href=\"/stop\">zurück</a>\n"
        "</body>\n"
        "</html>\n";


        String HTML_PULSE = 
        "<!DOCTYPE html>\n"
        "<html lang=\"de\">\n"
        "<head>\n"
        "    <meta charset=\"UTF-8\">\n"
        "    <meta name=\"viewport\" content=\"width=device-width, initial-scale=1.0\">\n"
        "    <title>Document</title>\n"
        "</head>\n"
        "<body>\n"
        "    <h1>Pulse Labor</h1>\n"
        "    <a href=\"/stop\">stop</a>\n" +
        String(HTML_UPDATE_MAX_BRIGHTNESS) +
        String(HTML_UPDATE_ANIMATION_SPEED) +
        String(HTML_ANIMATION_INCREMENT) +
        "</body>\n"
        "<script>\n" + 
        String(JAVASCRIPT_UPDATE_MAX_BRIGHTNESS_FUNCTION) + 
        String(JAVASCRIPT_UPDATE_ANIMATION_SPEED_FUNCTION) +
        String(JAVASCRIPT_SET_ANIMATION_INCREMENT) +
        "</script>\n"
        "</html>\n";


        String HTML_WAVE = 
        "<!DOCTYPE html>\n"
        "<html lang=\"de\">\n"
        "<head>\n"
        "    <meta charset=\"UTF-8\">\n"
        "    <meta name=\"viewport\" content=\"width=device-width, initial-scale=1.0\">\n"
        "    <title>Document</title>\n"
        "</head>\n"
        "<body>\n"
        "    <h1>Wave Labor</h1>\n"
        "    <a href=\"/stop\">stop</a>\n" +
        String(HTML_UPDATE_MAX_BRIGHTNESS) +
        String(HTML_UPDATE_ANIMATION_SPEED) +
        String(HTML_ANIMATION_INCREMENT) +
        "</body>\n"
        "<script>\n" + 
        String(JAVASCRIPT_UPDATE_MAX_BRIGHTNESS_FUNCTION) + 
        String(JAVASCRIPT_UPDATE_ANIMATION_SPEED_FUNCTION) +
        String(JAVASCRIPT_SET_ANIMATION_INCREMENT) +
        "</script>\n"
        "</html>\n";
};

#endif