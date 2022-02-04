/* All constant values for robot *
 * i.e. pins                     */

#ifndef CONSTS_H
#define CONSTS_H

// Serial
#define SERIAL_PORT_SPEED 115200
#define DEBUG_INTERVAL 200
#define DEBUG_ENABLED false

// RC Module
#define RC_SERIAL Serial1
#define TIMEOUT_INTERVAL 1000 // ms

// ESC Module
#define ESC_L_PIN 8
#define ESC_R_PIN 9

// PWM Constants
// these are the duration of PWM pulses in ms
#define PWM_MIN 1000
#define PWM_MAX 2000

// IMU Module
#define MPU_ENABLED false

// Status Indicators
#define LED_HALT  49
#define LED_NOSIG 51
#define LED_IMU   53

#endif