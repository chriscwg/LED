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
    *_animationSpeedMicros_ptr = 5000;
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

void MyLEDHandler::startWaveAnimation2(){
    *_current_animation_ptr = AnimationEnum::WAVE2;
    *_currentBrightnessGeschlossen_ptr = 5;
    *_currentBrightnessOffen_ptr = 5;
    *_animationSpeedMicros_ptr = 8500;
    *TAKT_ptr = true;
    Serial.println("wave2 started");
}

void MyLEDHandler::startBootAnimation(){
    *_current_animation_ptr = AnimationEnum::BOOT;
    Serial.println("Boot started");
    play_bootAnimation();
}

void MyLEDHandler::startWaveAnimation3(){
    *_current_animation_ptr = AnimationEnum::WAVE3;
    Serial.println("wave3 started");
}

void MyLEDHandler::startWaveAnimation4(){
    play_waveAnimation4();
    *_current_animation_ptr = AnimationEnum::WAVE4;
    Serial.println("wave4 started");
}

void MyLEDHandler::loop(){
    unsigned long currentMicros = micros();

    if (currentMicros - _previousMicros >= *_animationSpeedMicros_ptr){ 

        //linear interpolation formula to map 0-255 to _minBrightness-_maxBrightness
        int H_offen = _minBrightness + (((float)(_currentBrightnessOffen - 0)/(255 - 0)) * (_maxBrightness - _minBrightness));
        int H_geschlossen = _minBrightness + (((float)(_currentBrightnessGeschlossen - 0)/(255 - 0)) * (_maxBrightness - _minBrightness));

        analogWrite(_pinOffen, H_offen);   
        analogWrite(_pinGeschlossen, H_geschlossen);
        if(_pause > 0){
            *_pause_ptr = _pause - *_animationSpeedMicros_ptr;
            //dont call update_currentBrightness before the next 500 milliseconds
        }else{
            update_currentBrightness();
        }
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

void MyLEDHandler::setMinBrightness(int newMinBrightness){
    if(newMinBrightness >= 0 && newMinBrightness <= 200){
        *_minBrightness_ptr = newMinBrightness;
    }else{
        Serial.println("input invalid");
    }
}

void MyLEDHandler::setOffsetWave2(int newOffset){
    if(newOffset >= 5 && newOffset <= 200){
        *_offset_wave2_ptr = newOffset;
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
        case AnimationEnum::WAVE2:
            play_waveAnimation2();
            break;
        case AnimationEnum::BOOT:
            //nothing here because animation only plays once
            break;
        case AnimationEnum::WAVE3:
            play_waveAnimation3();
            break;
        case AnimationEnum::WAVE4:
            //nothing here because animation only plays once
            break;
    }
}

void MyLEDHandler::play_waveAnimation4(){
    for(int j=0; j<10; j++){
        for(int i=0; i<50; i++){
            analogWrite(_pinGeschlossen, i);
            delay(5);
        }
        for(int i=0; i<256; i++){
            analogWrite(_pinOffen, i);
            delay(5);
        }
        delay(50);
        for(int i=255; i>=0; i--){
            if(i<=50){
                analogWrite(_pinGeschlossen, i);
            }
            analogWrite(_pinOffen, i);
            delay(15);
        }

        delay(100);

        for(int i=0; i<50; i++){
            analogWrite(_pinOffen, i);
            delay(5);
        }
        for(int i=0; i<256; i++){
            analogWrite(_pinGeschlossen, i);
            delay(5);
        }
        delay(50);
        for(int i=255; i>=0; i--){
            if(i<=50){
                analogWrite(_pinOffen, i);
            }
            analogWrite(_pinGeschlossen, i);
            delay(15);
        }

        delay(100);
    }
}

void MyLEDHandler::play_waveAnimation2(){
    if(OFFEN_ON){
        *_currentBrightnessOffen_ptr += _animation_increment;
        if(*_currentBrightnessOffen_ptr >= 255){
            *OFFEN_ON_ptr = false;
        }
    }
    else if(!OFFEN_ON){
        if(*_currentBrightnessOffen_ptr > 5){
            *_currentBrightnessOffen_ptr -= _animation_increment;
            if(*_currentBrightnessOffen_ptr <= *_offset_wave2_ptr && !GESCHLOSSEN_ON){
                *GESCHLOSSEN_ON_ptr = true;
            }
        }
    }

    if(GESCHLOSSEN_ON){
        *_currentBrightnessGeschlossen_ptr += _animation_increment;
        if(*_currentBrightnessGeschlossen_ptr >= 255){
            *GESCHLOSSEN_ON_ptr = false;
        }
    }
    else if(!GESCHLOSSEN_ON){
        if(*_currentBrightnessGeschlossen_ptr > 5){
            *_currentBrightnessGeschlossen_ptr -= _animation_increment;
            if(*_currentBrightnessGeschlossen_ptr <= *_offset_wave2_ptr && !OFFEN_ON){
                *OFFEN_ON_ptr = true;
            }
        }
    }
}

void MyLEDHandler::play_waveAnimation3(){
    if(TAKT){
        if(TAKT_geschlossen){
            *_currentBrightnessGeschlossen_ptr += 1;
            *_currentBrightnessOffen_ptr = 5;
            if(*_currentBrightnessGeschlossen_ptr >= 255){
                *_pause_ptr = *_pause_on_max_brightness_value_ptr;
                TAKT_geschlossen = false;
            }
        }else{
            *_currentBrightnessGeschlossen_ptr -= 1;
            *_currentBrightnessOffen_ptr = 5;
            if(*_currentBrightnessGeschlossen_ptr <= 5){
                TAKT_geschlossen = true;
                *TAKT_ptr = false;
                *_pause_ptr = *_pause_totpunkt_ptr;
            }
        }
    }else{
        if(TAKT_offen){
            *_currentBrightnessOffen_ptr += 1;
            *_currentBrightnessGeschlossen_ptr = 5;
            if(*_currentBrightnessOffen_ptr >= 255){
                *_pause_ptr = *_pause_on_max_brightness_value_ptr;
                TAKT_offen = false;
            }
        }else{
            *_currentBrightnessOffen_ptr -= 1;
            *_currentBrightnessGeschlossen_ptr = 5;
            if(*_currentBrightnessOffen_ptr <= 5){
                TAKT_offen = true;
                *TAKT_ptr = true;
                *_pause_ptr = *_pause_totpunkt_ptr;
            }
        }
    }
}

void MyLEDHandler::setAnimationIncrement(int newAnimationIncrement){
    if(newAnimationIncrement >= 1 && newAnimationIncrement <= 5){
        *_animation_increment_ptr = newAnimationIncrement;
    }else{
        Serial.println("input invalid");
    }
}

void MyLEDHandler::setPauseOnMaxBrightness(int newPauseOnMaxBrightness){
    if(newPauseOnMaxBrightness >= 0 && newPauseOnMaxBrightness <= 5000){
        *_pause_on_max_brightness_value_ptr = newPauseOnMaxBrightness * 1000;
        Serial.println(*_pause_on_max_brightness_value_ptr);
    }else{
        Serial.println("input invalid");
    }
}

void MyLEDHandler::play_waveAnimation(){
    if(TAKT){
        _currentBrightnessOffen = _currentBrightnessOffen + _animation_increment;
        _currentBrightnessGeschlossen = _currentBrightnessGeschlossen - _animation_increment;

        if(_currentBrightnessOffen >= 255){
            *TAKT_ptr = !TAKT;                          //wave spezifische Variable
            *_pause_ptr = *_pause_on_max_brightness_value_ptr;     //allgemeine Variable
        }
    }else{
        _currentBrightnessOffen = _currentBrightnessOffen - _animation_increment;
        _currentBrightnessGeschlossen = _currentBrightnessGeschlossen + _animation_increment;

        if(_currentBrightnessOffen <= 0){
            *TAKT_ptr = !TAKT;                          //wave spezifische Variable
            *_pause_ptr = *_pause_on_max_brightness_value_ptr;     //allgemeine Variable
        }
    }
}

void MyLEDHandler::play_pulseAnimation(){
    if(_increasing__pulse){
        _currentBrightnessOffen = _currentBrightnessOffen + _animation_increment;
        if(_currentBrightnessOffen >= 255){
            _increasing__pulse = false;
            *_pause_ptr = *_pause_on_max_brightness_value_ptr;     //allgemeine Variable
        }
    }
    else {
        _currentBrightnessOffen = _currentBrightnessOffen - _animation_increment;
        if(_currentBrightnessOffen <= 0){
            _increasing__pulse = true;
        }
    }
    _currentBrightnessGeschlossen = _currentBrightnessOffen;  
}

void MyLEDHandler::play_bootAnimation(){
    for(int j=0; j<1; j++){
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

int MyLEDHandler::getAnimationSpeed(){
    return *_animationSpeedMicros_ptr;
}

int MyLEDHandler::getAnimationIncrement(){
    return *_animation_increment_ptr;
}

int MyLEDHandler::getMaxBrightness(){
    return *_maxBrightness_ptr;
}

int MyLEDHandler::getPauseOnMaxBrightness(){
    return (*_pause_on_max_brightness_value_ptr / 1000);
}

int MyLEDHandler::getMinBrightness(){
    return *_minBrightness_ptr;
}

int MyLEDHandler::getOffsetWave2(){
    return *_offset_wave2_ptr;
}