/* RC Transmission Submodule Design */
#ifndef RC_H
#define RC_H

#include"module.h"
#include"led_controller.h"

// RC Channels
#define RC_CH1  0
#define RC_CH2  1
#define RC_CH3  2
#define RC_CH4  3
#define RC_CH5  4
#define RC_CH6  5
#define RC_CH7  6
#define RC_CH8  7
#define RC_CH9  8
#define RC_CH10 9

class RC : public Module {
    public:
        enum speed {high, medium, low};

        // for interrupts to work, functions must be static (i.e. this needs to be a singleton class)
        RC(LEDController&);

        uint16_t getThrust();
        uint16_t getTurn();
        speed    getSpeed();
        bool     getTractionControl();
        bool     getGyroscopeCorrect();
        bool     isHalted();
        bool     isDisconnected();

        void run();
        void setup();
        void printDebug();
    private:
        // values range from PWM_MIN to PWM_MAX (1000ms to 2000ms)
        uint16_t getLeftStickX();
        uint16_t getLeftStickY();
        uint16_t getRightStickX();
        uint16_t getRightStickY();
        uint16_t getLeftKnob();
        uint16_t getRightKnob();
        uint16_t getSwitchA();
        uint16_t getSwitchB();
        uint16_t getSwitchC();
        uint16_t getSwitchD();

        int _prev_val[10];
        uint32_t _timeout;
        LEDController _leds;
};

#endif