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
    *_currentBrightnessGeschlossen_ptr = 0;
    *_currentBrightnessOffen_ptr = 0;
    Serial.println("pulse started");
}

void MyLEDHandler::stopAnimations(){
    *_current_animation_ptr = AnimationEnum::STOP;
    *_currentBrightnessGeschlossen_ptr = 0;
    *_currentBrightnessOffen_ptr = 0;
    Serial.println("stopped");
}

void MyLEDHandler::startWaveAnimation(){
    *_current_animation_ptr = AnimationEnum::WAVE;
    *_currentBrightnessGeschlossen_ptr = 255;
    *_currentBrightnessOffen_ptr = 0;
    Serial.println("wave started");
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
        case AnimationEnum::WAVE:
            play_waveAnimation();
            break;
    }
}

void MyLEDHandler::play_waveAnimation(){
    if(TAKT){
        _currentBrightnessOffen = _currentBrightnessOffen + 1;
        _currentBrightnessGeschlossen = _currentBrightnessGeschlossen - 1;

        

        if(_currentBrightnessOffen >= 255){
            *TAKT_ptr = !TAKT;            
        }
    }else{
        _currentBrightnessOffen = _currentBrightnessOffen - 1;
        _currentBrightnessGeschlossen = _currentBrightnessGeschlossen + 1;


        if(_currentBrightnessOffen <= 0){
            *TAKT_ptr = !TAKT;
        }
    }
}

void MyLEDHandler::play_pulseAnimation(){
    if(_increasing__pulse){
        _currentBrightnessOffen = _currentBrightnessOffen + 1;
        if(_currentBrightnessOffen >= 255){
            _increasing__pulse = false;
        }
    }
    else {
        _currentBrightnessOffen = _currentBrightnessOffen - 1;
        if(_currentBrightnessOffen == 0){
            _increasing__pulse = true;
        }
    }
    _currentBrightnessGeschlossen = _currentBrightnessOffen;  
}