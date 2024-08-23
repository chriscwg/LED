#ifndef MYWEBHANDLER_H
#define MYWEBHANDLER_H

#include "WebServer.h"

class MyWebHandler {
    public:
        MyWebHandler();
        void setup(const char* ssid, const char* password);
        void loop();
    private:
        void handleRoot();
        void test();
        WebServer _server;
};

#endif