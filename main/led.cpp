/* Implementation of LED class */

#include<Arduino.h>
#include"led.h"

LED::LED(uint32_t pin) : _pin(pin) {
    pinMode(_pin, OUTPUT);
    _status = status::off;
    _state = false;
}

void LED::setOn() {
    _status = status::on;
    _state = true;
    digitalWrite(_pin, HIGH);
}

void LED::setOff() {
    _status = status::off;
    _state = true;
    digitalWrite(_pin, LOW);
}

void LED::setBlink() {
    _status = status::blink;
}

LED::status LED::getStatus() {
    return _status;
}

void LED::toggle() {
    _state = !_state;
    digitalWrite(_pin, _state);
}

void LED::printDebug() {
    switch(_status) {
        case status::on:
            Serial.print("on");
            break;
        case status::blink:
            Serial.print("blink");
            break;
        case status::off:
            Serial.print("off");
            break;
    }
}
