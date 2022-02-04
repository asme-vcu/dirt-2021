/* All constant values for robot *
 * i.e. pins                     */

#ifndef CONSTS_H
#define CONSTS_H

// all numbers are either pins or times in ms

// Serial
#define SERIAL_PORT_SPEED 115200
#define DEBUG_INTERVAL 200
#define DEBUG_ENABLED false

// RC Module
#define RC_SERIAL Serial1
#define TIMEOUT_INTERVAL 1000

// Drive Module
#define DRIVE_ESC_L_PIN 8
#define DRIVE_ESC_R_PIN 9
#define DRIVE_TRACTION_CONTROL_ENABLED false
#define DRIVE_GYRO_EFFECTS_ENABLED     false
#define DRIVE_THRUST_WEIGHT 1.0f
#define DRIVE_TURN_WEIGHT   0.5f

// PWM Constants
// all in ms
#define PWM_MIN 1000
#define PWM_MAX 2000

// IMU Module
#define MPU_ENABLED false

// :ED Controller Module
#define LED_HALT  49
#define LED_NOSIG 51
#define LED_IMU   53
#define LED_BLINK_INTERVAL 500

#endif