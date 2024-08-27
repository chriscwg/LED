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
        WebServer _server;
        MyLEDHandler _myLEDHandler;




        const char HTML_ROOT[888] = 
        "<!DOCTYPE html>\n"
        "<html lang=\"en\">\n"
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
        "</body>\n"
        "</html>\n";



        const char HTML_PULSE[888] = 
        "<!DOCTYPE html>\n"
        "<html lang=\"en\">\n"
        "<head>\n"
        "    <meta charset=\"UTF-8\">\n"
        "    <meta name=\"viewport\" content=\"width=device-width, initial-scale=1.0\">\n"
        "    <title>Document</title>\n"
        "</head>\n"
        "<body>\n"
        "    <h1>Pulse Labor</h1>\n"
        "    <a href=\"/stop\">stop</a>\n"
        "</body>\n"
        "</html>\n";


        const char HTML_WAVE[888] = 
        "<!DOCTYPE html>\n"
        "<html lang=\"en\">\n"
        "<head>\n"
        "    <meta charset=\"UTF-8\">\n"
        "    <meta name=\"viewport\" content=\"width=device-width, initial-scale=1.0\">\n"
        "    <title>Document</title>\n"
        "</head>\n"
        "<body>\n"
        "    <h1>Wave Labor</h1>\n"
        "    <a href=\"/stop\">stop</a>\n"
        "</body>\n"
        "</html>\n";
};

#endif