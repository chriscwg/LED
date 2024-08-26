#include <Arduino.h>
#include "MyLEDHandler.h"
#include "AnimationEnum.h"

MyLEDHandler::MyLEDHandler(int pinOffen, int pinGeschlossen) : _pinOffen(pinOffen), _pinGeschlossen(pinGeschlossen){
    pinMode(_pinOffen, OUTPUT);
    pinMode(_pinGeschlossen, OUTPUT);
}

void MyLEDHandler::test(){
    Serial.println("TEST");
}

void MyLEDHandler::startPulseAnimation(){
    *_current_animation_ptr = AnimationEnum::PULSE;
    Serial.println("pulse started");
}

void MyLEDHandler::stopAnimations(){
    *_current_animation_ptr = AnimationEnum::STOP;
    *_currentBrightnessGeschlossen_ptr = 0;
    *_currentBrightnessOffen_ptr = 0;
    Serial.println("stopped");
}

void MyLEDHandler::loop(){
    unsigned long currentMillis = millis();

    if (currentMillis - _previousMillis >= *_animationSpeed_ptr){  
        analogWrite(_pinOffen, _currentBrightnessOffen);
        analogWrite(_pinGeschlossen, _currentBrightnessGeschlossen);
        update_currentBrightness();
        _previousMillis = currentMillis;
    }
}

void MyLEDHandler::update_currentBrightness(){
    switch(_current_animation){
        case AnimationEnum::PULSE:
            play_pulseAnimation();
            break;     
    }
}

void MyLEDHandler::play_pulseAnimation(){
    if(_increasing){
        _currentBrightnessOffen = _currentBrightnessOffen + 1;
        if(_currentBrightnessOffen >= 255){
            _increasing = false;
        }
    }
    else {
        _currentBrightnessOffen = _currentBrightnessOffen - 1;
        if(_currentBrightnessOffen == 0){
            _increasing = true;
        }
    }
    _currentBrightnessGeschlossen = _currentBrightnessOffen;  
}