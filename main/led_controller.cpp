/* LED Controller submodule implementation */

#include<Arduino.h>
#include"led_controller.h"
#include"consts.h"

LEDController::LEDController() : _imu(LED(LED_IMU)), _sig(LED(LED_NOSIG)), _hlt(LED(LED_HALT)) {}

void LEDController::setup() {
    _timer = millis();
}

void LEDController::run() {
    if(millis() > _timer + LED_BLINK_INTERVAL) {
        if(_imu.getStatus() == LED::status::blink) {
            _imu.toggle();
        }
        if(_sig.getStatus() == LED::status::blink) {
            _sig.toggle();
        }
        if(_hlt.getStatus() == LED::status::blink) {
            _hlt.toggle();
        }
        _timer = millis();
    }
}

void LEDController::reset() {
    _imu.setOff();
    _sig.setOff();
    _hlt.setOff();
}

LED LEDController::imu() {
    return _imu;
}

LED LEDController::sig() {
    return _sig;
}

LED LEDController::hlt() {
    return _hlt;
}

void LEDController::printDebug() {
    Serial.println("[LED Module]");
    Serial.print("IMU: "); 
    _imu.printDebug();
    Serial.print(" SIG: ");
    _sig.printDebug();
    Serial.print(" HLT: ");
    _hlt.printDebug();
    Serial.println();
}
