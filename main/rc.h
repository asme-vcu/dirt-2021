/* RC Transmission Submodule Design */
#ifndef RC_H
#define RC_H

#include"module.h"
#include<stdint.h>

#define RC_NUM_CHANNELS 6

class RC : public Module {
    public:
        // for interrupts to work, functions must be static (i.e. this needs to be a singleton class)
        static RC* getInstance();
        // values range from 1000 to 2000
        uint16_t getLeftStickX();
        uint16_t getLeftStickY();
        uint16_t getRightStickX();
        uint16_t getRightStickY();
        uint16_t getLeftKnob();
        uint16_t getRightKnob();

        void run();
        void setup();
        void printDebug();
    private:
        static RC *instance;
        RC();

        // internal array of stable values
        static uint16_t rc_values[RC_NUM_CHANNELS];
        // timers to measure pulse widths
        static uint32_t rc_timer[RC_NUM_CHANNELS];
        // this memory is modified during an interrupt, hence volatile
        static volatile uint16_t rc_shared[RC_NUM_CHANNELS];

        static void ch1_interrupt();
        static void ch2_interrupt();
        static void ch3_interrupt();
        static void ch4_interrupt();
        static void ch5_interrupt();
        static void ch6_interrupt();

        void read_rc_values();
        static void calc_input(uint8_t channel, uint8_t input_pin);
};

#endif