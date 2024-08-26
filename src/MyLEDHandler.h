#ifndef MYLEDHANDLER_H
#define MYLEDHANDLER_H

#include "AnimationEnum.h"

class MyLEDHandler{
    public:
        MyLEDHandler(int pinOffen, int pinGeschlossen);
        void loop();
        
        //funktionen, die von myWebHandler aufgerufen werden
        void test();
        void startPulseAnimation();
        void stopAnimations();
        int _pinOffen;
        int _pinGeschlossen;
        int _animationSpeed = 5; //animationSpeed refers to the time between a change in brightness
        int _currentBrightnessOffen = 0;
        int _currentBrightnessGeschlossen = 0;
        unsigned long _previousMillis = 0;
        boolean _increasing = true;
    private:
        AnimationEnum _current_animation = AnimationEnum::PULSE;
        AnimationEnum* _current_animation_ptr = &_current_animation;
        //int _current_animation_int = 0;
        //int* _current_animation_int_ptr = &_current_animation_int;
        //volatile int _current_animation_int = 0;
        void update_currentBrightness();
};


#endif