/* RC Transmission Submodule Implementation */
#include<Arduino.h>
#include"rc.h"
#include"consts.h"
#include"FlySkyIBus.h"

RC::RC(LEDController& leds) : _leds(leds) {
    for(int i = 0; i < 10; i++) {
        _prev_val[i] = -1000;
    }
}

void RC::setup() {
    IBus.begin(RC_SERIAL);
    _timeout = millis();
}

void RC::run() {
    IBus.loop();

    bool same = true;
    for(int i = 0; i < 10; i++) {
        if(_prev_val[i] != IBus.readChannel(i)) {
            same = false;
            _prev_val[i] = IBus.readChannel(i);
        }
    }
    if(!same) _timeout = millis();

    if(isDisconnected()) {
        _leds.sig().setOn();
    } else {
        _leds.sig().setOff();
    }

    if(isHalted()) {
        _leds.hlt().setOn();
    } else {
        _leds.hlt().setOff();
    }
}


void RC::printDebug() {
    Serial.println("[RC Module]");
    Serial.print("CH1:");  Serial.print(map(IBus.readChannel(RC_CH1),  PWM_MIN, PWM_MAX, -100, 100)); Serial.print("\t");
    Serial.print("CH2:");  Serial.print(map(IBus.readChannel(RC_CH2),  PWM_MIN, PWM_MAX, -100, 100)); Serial.print("\t");
    Serial.print("CH3:");  Serial.print(map(IBus.readChannel(RC_CH3),  PWM_MIN, PWM_MAX, -100, 100)); Serial.print("\t");
    Serial.print("CH4:");  Serial.print(map(IBus.readChannel(RC_CH4),  PWM_MIN, PWM_MAX, -100, 100)); Serial.print("\t");
    Serial.print("CH5:");  Serial.print(map(IBus.readChannel(RC_CH5),  PWM_MIN, PWM_MAX, -100, 100)); Serial.print("\t");
    Serial.print("CH6:");  Serial.print(map(IBus.readChannel(RC_CH6),  PWM_MIN, PWM_MAX, -100, 100)); Serial.print("\t");
    Serial.print("CH7:");  Serial.print(map(IBus.readChannel(RC_CH7),  PWM_MIN, PWM_MAX, 0, 2)); Serial.print("\t");
    Serial.print("CH8:");  Serial.print(map(IBus.readChannel(RC_CH8),  PWM_MIN, PWM_MAX, 0, 2)); Serial.print("\t");
    Serial.print("CH9:");  Serial.print(map(IBus.readChannel(RC_CH9),  PWM_MIN, PWM_MAX, 0, 2)); Serial.print("\t");
    Serial.print("CH10:"); Serial.print(map(IBus.readChannel(RC_CH10), PWM_MIN, PWM_MAX, 0, 2)); Serial.print("\n");
}

uint16_t RC::getThrust() {
    return getRightStickY();
}

uint16_t RC::getTurn() {
    return getLeftStickX();
}

RC::speed RC::getSpeed() {
    uint16_t speed = getSwitchC();

    if(speed > 1700) {
        return RC::speed::high;
    } else if(speed < 1300) {
        return RC::speed::low;
    } else {
        return RC::speed::medium;
    }
}

// must turn ON
bool RC::getTractionControl() {
    return getSwitchA() > 1500;
}

// must turn ON
bool RC::getGyroscopeCorrect() {
    return getSwitchB() > 1500;
}

// must turn OFF
bool RC::isHalted() {
    return getSwitchC() < 1500;
}

bool RC::isDisconnected() {
    return millis() > _timeout + TIMEOUT_INTERVAL;
}

// raw controller values
uint16_t RC::getLeftStickX()  { return IBus.readChannel(RC_CH4);  }
uint16_t RC::getLeftStickY()  { return IBus.readChannel(RC_CH3);  }
uint16_t RC::getRightStickX() { return IBus.readChannel(RC_CH1);  }
uint16_t RC::getRightStickY() { return IBus.readChannel(RC_CH2);  }
uint16_t RC::getLeftKnob()    { return IBus.readChannel(RC_CH5);  }
uint16_t RC::getRightKnob()   { return IBus.readChannel(RC_CH6);  }
uint16_t RC::getSwitchA()     { return IBus.readChannel(RC_CH7);  }
uint16_t RC::getSwitchB()     { return IBus.readChannel(RC_CH8);  }
uint16_t RC::getSwitchC()     { return IBus.readChannel(RC_CH9);  }
uint16_t RC::getSwitchD()     { return IBus.readChannel(RC_CH10); }
