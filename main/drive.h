/* Drive-train control logic sub-module */
#ifndef DRIVE_H
#define DRIVE_H

#include<Servo.h>
#include"imu.h"
#include"rc.h"
#include"module.h"

class Drive : public Module {
    public:
        // Keep track of different velocities
        struct Velocity {
            float left, right;
        };

        // Constructor, drive needs access to the IMU and RC modules
        Drive(IMU&, RC&);

        // Standard module functions
        void setup();
        void run();
        void printDebug();
    private:
        // Test if the car should halt
        bool     shouldHalt();
        // Get target velocity from remote input
        Velocity getTarget();
        // Applies traction control to the target velocity
        Velocity applyTractionControl(Velocity);
        // Applies gyroscopic control to the target velocity
        Velocity applyGyroControl(Velocity);
        // Sets the speed of the motors to a velocity
        void setSpeed(Velocity);

        // Bools for checking if traction control or gyro control is enabled
        bool _tractionControl, _gyroControl;

        // Previous time and velocity from last loop iteration
        Velocity _prevVelocity;
        uint32_t _prevTime;

        // Delta time and Delta velocity for traction control
        long _dt;
        Velocity _dv;

        // Reference to IMU module for gyro
        IMU& _imu;
        // Reference to RC module for inputs
        RC& _rc;

        // ESC's of our actual car to apply drive controls
        Servo _esc_l;
        Servo _esc_r;
};

#endif