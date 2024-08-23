#ifndef MYWEBHANDLER_H
#define MYWEBHANDLER_H

#include "WebServer.h"

class MyWebHandler {
    public:
        MyWebHandler();
        void setup();
        void loop();
    private:
        void handleRoot();
        WebServer _server;
};

#endif