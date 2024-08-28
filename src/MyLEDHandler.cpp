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

void MyLEDHandler::startBootAnimation(){
    *_current_animation_ptr = AnimationEnum::BOOT;
    Serial.println("Boot started");
    play_bootAnimation();
}


void MyLEDHandler::loop(){
    unsigned long currentMicros = micros();

    if (currentMicros - _previousMicros >= *_animationSpeedMicros_ptr){ 
        analogWrite(_pinOffen, (_currentBrightnessOffen * _maxBrightness) / 255);                   //map 0-255 zu 0-_maxBrightness
        analogWrite(_pinGeschlossen, (_currentBrightnessGeschlossen * _maxBrightness) / 255);       //map 0-255 zu 0-_maxBrightness
        update_currentBrightness();
        _previousMicros = currentMicros;
    }
}

void MyLEDHandler::setMaxBrightness(int newBrightness){
    if(newBrightness >= 0 && newBrightness <= 255){
        *_maxBrightness_ptr = newBrightness;
    }else{
        Serial.println("input invalid");
    }
}

void MyLEDHandler::setAnimationSpeed(int newAnimationSpeed){
    if(newAnimationSpeed >= 1250 && newAnimationSpeed <= 10000){
        *_animationSpeedMicros_ptr = newAnimationSpeed;
    }else{
        Serial.println("input invalid");
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
        case AnimationEnum::BOOT:
            //nothing here because animation only plays once
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
        if(_currentBrightnessOffen <= 0){
            _increasing__pulse = true;
        }
    }
    _currentBrightnessGeschlossen = _currentBrightnessOffen;  
}

void MyLEDHandler::play_bootAnimation(){
    for(int j=0; j<3; j++){
        for(int i=0; i<101; i++){
            analogWrite(_pinGeschlossen, 100-i);
            analogWrite(_pinOffen, i);
            delay(5);
        }
        delay(50);
        for(int i=0; i<101; i++){
            analogWrite(_pinOffen, 100-i);
            analogWrite(_pinGeschlossen, i);
            delay(5);
        }
        delay(50);
    }
    for(int i=0; i<101; i++){
        analogWrite(_pinGeschlossen, 100-i);
        delay(5);
    }
    delay(100);
    for(int i=0; i<255; i++){
        analogWrite(_pinGeschlossen, i);
        analogWrite(_pinOffen, i);
        delay(5);
    }
    analogWrite(_pinGeschlossen, 255);
    analogWrite(_pinOffen, 255);
    delay(1000);
    for(int i=0; i<256; i++){
        analogWrite(_pinGeschlossen, 255-i);
        analogWrite(_pinOffen, 255-i);
        delay(8);
    }
    *_currentBrightnessGeschlossen_ptr = 0;
    *_currentBrightnessOffen_ptr = 0;
}