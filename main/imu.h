/* IMU Sensor Submodule Design */
#ifndef IMU_H
#define IMU_H

#include<Adafruit_MPU6050.h>
#include"module.h"
#include"led_controller.h"

class IMU : public Module {
    public:
        // Constructor
        IMU(LEDController&);
        // values range from -180 to 180
        float getPitch(); // pitch of nose up and down
        float getYaw();   // rotation of nose left and right
        float getRoll();  // roll of nose clockwise and counterclockwise
        float getAccelX();
        float getAccelY();
        float getAccelZ();
        float getVelocityX();
        float getVelocityY();
        float getVelocityZ();

        bool getEnabled();

        void run();
        void setup();
        void printDebug();
    private:
        LEDController _leds;
        Adafruit_MPU6050 _mpu;
        sensors_event_t _acc, _gyro, _temp;
        bool _enabled;
};

#endif