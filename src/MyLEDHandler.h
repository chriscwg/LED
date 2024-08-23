#ifndef MYLEDHANDLER_H
#define MYLEDHANDLER_H


class MyLEDHandler{
    public:
        MyLEDHandler(int pinOffen, int pinGeschlossen);
        void setup(); // int pinOffen, int pinGeschlossen);
        void loop();
        
        //funktionen, die von myWebHandler aufgerufen werden
        void test();
        void startPulseAnimation();

    private:
        int _pinOffen;
        int _pinGeschlossen;
        int _animationSpeed; //animationSpeed refers to the time between a change in brightness
        int _currentBrightnessOffen;
        int _currentBrightnessGeschlossen;
        unsigned long _previousMillis;
        boolean _increasing;
        String _current_animation;

        void update_currentBrightness();
};


#endif