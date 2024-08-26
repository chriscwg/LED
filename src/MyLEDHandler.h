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
        
        
    private:
        int _pinOffen;
        int _pinGeschlossen;
        AnimationEnum _current_animation = AnimationEnum::STOP;
        AnimationEnum* _current_animation_ptr = &_current_animation;
        boolean _increasing = true;

        int _animationSpeed = 5; //animationSpeed refers to the time between a change in brightness
        int* _animationSpeed_ptr = &_animationSpeed;

        int _currentBrightnessOffen = 0;
        int* _currentBrightnessOffen_ptr = &_currentBrightnessOffen;
        int _currentBrightnessGeschlossen = 0;
        int* _currentBrightnessGeschlossen_ptr = &_currentBrightnessGeschlossen;
        unsigned long _previousMillis = 0;
        
        void update_currentBrightness();
        void play_pulseAnimation();
};


#endif