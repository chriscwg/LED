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
        void setPauseOnMaxBrightness();
        void setMinBrightness();
        void startWaveAnimation2();
        void setOffsetWave2();
        void startWaveAnimation3();
        void startWaveAnimation4();

        WebServer _server;
        MyLEDHandler _myLEDHandler;


        String JAVASCRIPT_UPDATE_MAX_BRIGHTNESS_FUNCTION =
        "   function updateMaxBrightness(value){\n"
        "       document.getElementById('maxBrightnessP').textContent = 'Helligkeit:' + value.toString()\n"
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

        String JAVASCRIPT_SET_PAUSE_ON_MAX_BRIGHTNESS =
        "   function setPauseOnMaxBrightness(value){\n"
        "       document.getElementById('pauseOnMaxBrightnessP').textContent = 'Pause bei maximaler Helligkeit (ms):' + value.toString()\n"
        "       fetch('http://192.168.4.1/setPauseOnMaxBrightness', {\n"
        "           method: 'POST',\n"
        "           headers: {\n"
        "                'Content-Type': 'application/json'\n"
        "           },\n"
        "           body: JSON.stringify({ newPauseOnMaxBrightness: value })\n"
        "       })\n"
        "       .then(response => response.json())\n"
        "       .then(data => console.log(data))\n"
        "       .catch(error => console.error('Error:', error));\n"
        "   }\n";

        String JAVASCRIPT_SET_MIN_BRIGHTNESS =
        "   function setMinBrightness(value){\n"
        "       document.getElementById('minBrightnessP').textContent = 'Minimale Helligkeit: ' + value.toString()\n"
        "       fetch('http://192.168.4.1/setMinBrightness', {\n"
        "           method: 'POST',\n"
        "           headers: {\n"
        "                'Content-Type': 'application/json'\n"
        "           },\n"
        "           body: JSON.stringify({ newMinBrightness: value })\n"
        "       })\n"
        "       .then(response => response.json())\n"
        "       .then(data => console.log(data))\n"
        "       .catch(error => console.error('Error:', error));\n"
        "   }\n";

        String JAVASCRIPT_SET_OFFSET_WAVE2 =
        "   function setOffsetWave2(value){\n"
        "       document.getElementById('offsetP').textContent = 'Offset: ' + value.toString()\n"
        "       fetch('http://192.168.4.1/setOffsetWave2', {\n"
        "           method: 'POST',\n"
        "           headers: {\n"
        "                'Content-Type': 'application/json'\n"
        "           },\n"
        "           body: JSON.stringify({ newOffset: value })\n"
        "       })\n"
        "       .then(response => response.json())\n"
        "       .then(data => console.log(data))\n"
        "       .catch(error => console.error('Error:', error));\n"
        "   }\n";

         String HTML_UPDATE_OFFSET_WAVE2 = 
        "    <center><p id=\"offsetP\">Offset: ({OFFSET_PLATZHALTER})</p></center>\n"
        "    <center><input type=\"range\" min=\"5\" max=\"200\" value=\"{OFFSET_PLATZHALTER}\" id=\"offset\" onchange=\"setOffsetWave2(this.value)\"></center>\n";

        String HTML_UPDATE_ANIMATION_SPEED = 
        "    <center><p id=\"animationSpeedP\">Gesamtdauer: ({ANIMATION_SPEED_PLATZHALTER})</p></center>\n"
        "    <center><input type=\"range\" min=\"1250\" max=\"10000\" value=\"{ANIMATION_SPEED_PLATZHALTER}\" id=\"animationSpeed\" onchange=\"updateAnimationSpeed(this.value)\"></center>\n";
        
        String HTML_SET_MIN_BRIGHTNESS = 
        "    <center><p id=\"minBrightnessP\">Minimale Helligkeit: ({MIN_BRIGHTNESS_PLATZHALTER})</p></center>\n"
        "    <center><input type=\"range\" min=\"0\" max=\"200\" value=\"{MIN_BRIGHTNESS_PLATZHALTER}\" id=\"minBrightness\" onchange=\"setMinBrightness(this.value)\"></center>\n";
        
        String HTML_SET_PAUSE_ON_MAX_BRIGHTNESS = 
        "    <center><p id=\"pauseOnMaxBrightnessP\">Pause bei maximaler Helligkeit (ms): {PAUSE_ON_MAX_BRIGHTNESS_PLATZHALTER}</p></center>\n"
        "    <center><input type=\"range\" min=\"0\" max=\"1000\" value=\"{PAUSE_ON_MAX_BRIGHTNESS_PLATZHALTER}\" id=\"pauseOnMaxBrigthness\" onchange=\"setPauseOnMaxBrightness(this.value)\"></center>\n";

        String HTML_UPDATE_MAX_BRIGHTNESS = 
        "    <center><p id=\"maxBrightnessP\">Helligkeit: {MAX_BRIGHTNESS_PLATZHALTER}</p></center>\n"
        "    <center><input type=\"range\" min=\"0\" max=\"255\" value=\"{MAX_BRIGHTNESS_PLATZHALTER}\" id=\"maxBrightness\" onchange=\"updateMaxBrightness(this.value)\"></center>\n";

        String JAVASCRIPT_SET_ANIMATION_INCREMENT =
        "   function setAnimationIncrement(value){\n"
        "       document.getElementById('animationIncrementP').textContent = 'Hebel: x' + value.toString(); \n"
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
        "   <center><p id=\"animationIncrementP\">Hebel: x{ANIMATION_INCREMENT_PLATZHALTER}</p></center>"
        "   <center><button onclick='setAnimationIncrement(1)'>x1</button>\n"
        "   <button onclick='setAnimationIncrement(2)'>x2</button>\n"
        "   <button onclick='setAnimationIncrement(3)'>x3</button></center>\n";

        const char HTML_ROOT[1500] = 
        "<!DOCTYPE html>\n"
        "<html lang=\"de\">\n"
        "<head>\n"
        "    <meta charset=\"UTF-8\">\n"
        "    <meta name=\"viewport\" content=\"width=device-width, initial-scale=1.0, shrink-to-fit=no\">\n"
        "    <title>Document</title>\n"
        "</head>\n"
        "<body>\n"
        "    <center><h1>LED Steuerung</h1></center>\n"
        "    <center><h2>Pulse-Labor</h2></center>\n"
        "    <center><a href=\"/startPulseAnimation\">start</a></center>\n"
        "    <center><h2>Wave-Labor</h2></center>\n"
        "    <center><a href=\"/startWaveAnimation\">start</a></center>\n"
        "    <center><h2>Wave2-Labor</h2></center>\n"
        "    <center><a href=\"/startWaveAnimation2\">start</a></center>\n"
        "    <center><h2>BOOT</h2></center>\n"
        "    <center><a href=\"/startBootAnimation\">start</a></center>\n"
        "    <center><h2>ZIEMLICHE WELLE</h2></center>\n"
        "    <center><a href=\"/startWaveAnimation4\">start</a></center>\n"
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

        const char HTML_WAVE4[888] = 
        "<!DOCTYPE html>\n"
        "<html lang=\"de\">\n"
        "<head>\n"
        "    <meta charset=\"UTF-8\">\n"
        "    <meta name=\"viewport\" content=\"width=device-width, initial-scale=1.0\">\n"
        "    <title>Document</title>\n"
        "</head>\n"
        "<body>\n"
        "    <center><h1>WAVE 4</h1></center>\n"
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
        "    <center><h1>Pulse Labor</h1></center>\n"
        "    <center><a href=\"/stop\">stop</a></center>\n" +
        String(HTML_UPDATE_MAX_BRIGHTNESS) +
        String(HTML_UPDATE_ANIMATION_SPEED) +
        String(HTML_ANIMATION_INCREMENT) +
        String(HTML_SET_PAUSE_ON_MAX_BRIGHTNESS) +
        String(HTML_SET_MIN_BRIGHTNESS) +
        "</body>\n"
        "<script>\n" + 
        String(JAVASCRIPT_UPDATE_MAX_BRIGHTNESS_FUNCTION) + 
        String(JAVASCRIPT_UPDATE_ANIMATION_SPEED_FUNCTION) +
        String(JAVASCRIPT_SET_ANIMATION_INCREMENT) +
        String(JAVASCRIPT_SET_PAUSE_ON_MAX_BRIGHTNESS) +
        String(JAVASCRIPT_SET_MIN_BRIGHTNESS) +
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
        "    <center><h1>Wave Labor</h1></center>\n"
        "    <center><a href=\"/stop\">stop</a></center>\n" +
        String(HTML_UPDATE_MAX_BRIGHTNESS) +
        String(HTML_UPDATE_ANIMATION_SPEED) +
        String(HTML_ANIMATION_INCREMENT) +
        String(HTML_SET_PAUSE_ON_MAX_BRIGHTNESS) +
        String(HTML_SET_MIN_BRIGHTNESS) +
        "</body>\n"
        "<script>\n" + 
        String(JAVASCRIPT_UPDATE_MAX_BRIGHTNESS_FUNCTION) + 
        String(JAVASCRIPT_UPDATE_ANIMATION_SPEED_FUNCTION) +
        String(JAVASCRIPT_SET_ANIMATION_INCREMENT) +
        String(JAVASCRIPT_SET_PAUSE_ON_MAX_BRIGHTNESS) +
        String(JAVASCRIPT_SET_MIN_BRIGHTNESS) +
        "</script>\n"
        "</html>\n";

        String HTML_WAVE2 = 
        "<!DOCTYPE html>\n"
        "<html lang=\"de\">\n"
        "<head>\n"
        "    <meta charset=\"UTF-8\">\n"
        "    <meta name=\"viewport\" content=\"width=device-width, initial-scale=1.0\">\n"
        "    <title>Document</title>\n"
        "</head>\n"
        "<body>\n"
        "    <center><h1>Wave Labor 2</h1></center>\n"
        "    <center><a href=\"/stop\">stop</a></center>\n" +
        String(HTML_UPDATE_MAX_BRIGHTNESS) +
        String(HTML_UPDATE_ANIMATION_SPEED) +
        String(HTML_ANIMATION_INCREMENT) +
        String(HTML_SET_MIN_BRIGHTNESS) +
        String(HTML_UPDATE_OFFSET_WAVE2) +
        "</body>\n"

        "<script>\n" + 
        String(JAVASCRIPT_UPDATE_MAX_BRIGHTNESS_FUNCTION) + 
        String(JAVASCRIPT_UPDATE_ANIMATION_SPEED_FUNCTION) +
        String(JAVASCRIPT_SET_ANIMATION_INCREMENT) +
        String(JAVASCRIPT_SET_MIN_BRIGHTNESS) +
        String(JAVASCRIPT_SET_OFFSET_WAVE2) +
        "</script>\n"
        "</html>\n";

        String HTML_WAVE3 =
       "<!DOCTYPE html>\n"
        "<html lang=\"de\">\n"
        "<head>\n"
        "    <meta charset=\"UTF-8\">\n"
        "    <meta name=\"viewport\" content=\"width=device-width, initial-scale=1.0\">\n"
        "    <title>Document</title>\n"
        "</head>\n"
        "<body>\n"
        "    <center><h1>Wave Labor 3</h1></center>\n"
        "    <center><a href=\"/stop\">stop</a></center>\n" +
        String(HTML_UPDATE_MAX_BRIGHTNESS) +
        String(HTML_UPDATE_ANIMATION_SPEED) +
        String(HTML_ANIMATION_INCREMENT) +
        String(HTML_SET_PAUSE_ON_MAX_BRIGHTNESS) +
        //here -> SET_PAUSE_ON_TOTPUNKT
        "</body>\n"
        "<script>\n" + 
        String(JAVASCRIPT_UPDATE_MAX_BRIGHTNESS_FUNCTION) + 
        String(JAVASCRIPT_UPDATE_ANIMATION_SPEED_FUNCTION) +
        String(JAVASCRIPT_SET_ANIMATION_INCREMENT) +
        String(JAVASCRIPT_SET_PAUSE_ON_MAX_BRIGHTNESS) +
        //here -> SET_PAUSE_ON_TOTPUNKT
        "</script>\n"
        "</html>\n";
};

#endif