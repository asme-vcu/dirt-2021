/* LED Controller submodule */

#ifndef LED_CONTROLLER_H
#define LED_CONTROLLER_H

#include"module.h"
#include"led.h"

class LEDController : public Module {
    public:
        LEDController();

        LED imu(); // IMU led
        LED sig(); // RC Connected led
        LED hlt(); // Halt led

        void reset();

        void setup();
        void run();
        void printDebug();

    private:
        LED _imu;
        LED _sig;
        LED _hlt;

        uint32_t _timer;
};

#endif