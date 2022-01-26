/* IMU Sensor Submodule Design */
#ifndef IMU_H
#define IMU_H

#include"module.h"
#include<I2Cdev.h>
#include<MPU6050_6Axis_MotionApps20.h>
#include<stdint.h>

#if I2CDEV_IMPLEMENTATION == I2CDEV_ARDUINO_WIRE
#include "Wire.h"
#endif

class IMU : public Module {
    public:
        // for interrupts to work, functions must be static (i.e. this needs to be a singleton class)
        static IMU* getInstance();
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
        static IMU *instance;
        IMU();

        MPU6050* mpu;

        bool goodConnection; // sets to true if IMU connection is valid

        // MPU control/status vars
        bool dmpReady;          // set true if DMP init was successful
        uint8_t mpuIntStatus;   // holds actual interrupt status byte from MPU
        uint8_t devStatus;      // return status after each device operation (0 = success, !0 = error)
        uint16_t packetSize;    // expected DMP packet size (default is 42 bytes)
        uint16_t fifoCount;     // count of all bytes currently in FIFO
        uint8_t fifoBuffer[64]; // FIFO storage buffer

        // orientation/motion vars
        Quaternion q;           // [w, x, y, z]         quaternion container
        VectorInt16 aa;         // [x, y, z]            accel sensor measurements
        VectorInt16 aaReal;     // [x, y, z]            gravity-free accel sensor measurements
        VectorInt16 aaWorld;    // [x, y, z]            world-frame accel sensor measurements
        VectorFloat gravity;    // [x, y, z]            gravity vector
        float euler[3];         // [psi, theta, phi]    Euler angle container
        float ypr[3];           // [yaw, pitch, roll]   yaw/pitch/roll container and gravity vector

        // interrupt handler
        static volatile bool mpuInterrupt;     // indicates whether MPU interrupt pin has gone high
        static void dmpDataReady();
};

#endif