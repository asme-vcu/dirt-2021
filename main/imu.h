/* IMU Sensor Submodule Design */
#ifndef IMU_H
#define IMU_H

#include<Adafruit_MPU6050.h>
#include"module.h"

class IMU : public Module {
    public:
        // Constructor
        IMU();
        // values range from -180 to 180
        float getPitch(); // pitch of nose up and down
        float getYaw();   // rotation of nose left and right
        float getRoll();  // roll of nose clockwise and counterclockwise
        uint16_t getAccelX();
        uint16_t getAccelY();
        uint16_t getAccelZ();

        void run();
        void setup();
        void printDebug();
    private:
        Adafruit_MPU6050 mpu;
        sensors_event_t acc, gyro, temp;
};

#endif