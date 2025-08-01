#ifndef MYLEDHANDLER_H
#define MYLEDHANDLER_H

#include "AnimationEnum.h"

class MyLEDHandler{
    public:
        MyLEDHandler(int pinOffen, int pinGeschlossen);
        void loop();
        
        //Funktionen, die von myWebHandler aufgerufen werden
        void test();
        void startPulseAnimation();
        void startWaveAnimation();
        void startBootAnimation();
        void stopAnimations();
        void setMaxBrightness(int);
        void setAnimationSpeed(int);
        void setAnimationIncrement(int);
        void setPauseOnMaxBrightness(int);
        void setMinBrightness(int);
        int getAnimationSpeed();
        int getAnimationIncrement();
        int getMaxBrightness();
        int getPauseOnMaxBrightness();
        int getMinBrightness();
        
    private:
        int _pinOffen;
        int _pinGeschlossen;

        AnimationEnum _current_animation = AnimationEnum::STOP;
        AnimationEnum* _current_animation_ptr = &_current_animation;

        //variablen für pulse Animation
        boolean _increasing__pulse = true;

        //variablen für wave Animation
        boolean TAKT = true;
        boolean* TAKT_ptr = &TAKT;

        //allgemeine Variablen für Animationen
        int _animationSpeedMicros = 5000;                   //animationSpeed refers to the time between a change in brightness (in Microsekunden = 1/100.000s)
        int* _animationSpeedMicros_ptr = &_animationSpeedMicros;

        int _currentBrightnessOffen = 0;
        int* _currentBrightnessOffen_ptr = &_currentBrightnessOffen;
        int _currentBrightnessGeschlossen = 0;
        int* _currentBrightnessGeschlossen_ptr = &_currentBrightnessGeschlossen;

        unsigned long _previousMicros = 0;

        int _maxBrightness = 255;
        int* _maxBrightness_ptr = &_maxBrightness;
        
        int _animation_increment = 1;
        int* _animation_increment_ptr = &_animation_increment;

        int _pause_on_max_brightness = 0;
        int* _pause_on_max_brightness_ptr = &_pause_on_max_brightness;

        int _pause_on_max_brightness_value = 0;
        int* _pause_on_max_brightness_value_ptr = &_pause_on_max_brightness_value;

        int _minBrightness = 50;
        int* _minBrightness_ptr = &_minBrightness;

        //private Funktionen
        void update_currentBrightness();
        void play_pulseAnimation();
        void play_waveAnimation();
        void play_bootAnimation();
};


#endif