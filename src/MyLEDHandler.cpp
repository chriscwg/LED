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
    _animationSpeed = 50;
    _currentBrightnessOffen = 100;
    _previousMillis = 0;
    _increasing = true;

    *_current_animation_ptr = AnimationEnum::PULSE;
    Serial.println("pulse started");
}

void MyLEDHandler::stopAnimations(){
    *_current_animation_ptr = AnimationEnum::STOP;
    Serial.println("stopped");
}

void MyLEDHandler::loop(){
    unsigned long currentMillis = millis();

    if (currentMillis - _previousMillis >= _animationSpeed){        
        analogWrite(_pinOffen, _currentBrightnessOffen);
        analogWrite(_pinGeschlossen, _currentBrightnessGeschlossen);
        update_currentBrightness();
        _previousMillis = currentMillis;
    }
}

void MyLEDHandler::update_currentBrightness(){
    if(*_current_animation_ptr == AnimationEnum::PULSE){
        if(_increasing){
            _currentBrightnessOffen++;
            if(_currentBrightnessOffen >= 255){
                _increasing = false;
            }
        }
        else {
            _currentBrightnessOffen--;
            if(_currentBrightnessOffen == 0){
                _increasing = true;
            }
        }
        _currentBrightnessGeschlossen = _currentBrightnessOffen;
    }
}