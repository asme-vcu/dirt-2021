/* All constant values for robot *
 * i.e. pins                     */

#ifndef CONSTS_H
#define CONSTS_H

// Serial
#define SERIAL_PORT_SPEED 115200
#define DEBUG_INTERVAL 200
#define DEBUG_ENABLED true

// RC Module
#define RC_SERIAL Serial1

// ESC Module
#define ESC_FL_PIN 8
#define ESC_FR_PIN 9
#define ESC_BL_PIN 10
#define ESC_BR_PIN 11

// PWM Constants
// these are the duration of PWM pulses in ms
#define PWM_MIN 1000
#define PWM_MAX 2000

// IMU Module
#define MPU_ENABLED true

#endif