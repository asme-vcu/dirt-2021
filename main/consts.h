/* All constant values for robot *
 * i.e. pins                     */

#ifndef CONSTS_H
#define CONSTS_H

// Serial
#define SERIAL_PORT_SPEED 9600
#define DEBUG_INTERVAL 200
#define DEBUG_ENABLED true

// RC Module
#define RC_CH1_PIN A0
#define RC_CH2_PIN A1
#define RC_CH3_PIN A2
#define RC_CH4_PIN A3
#define RC_CH5_PIN A4
#define RC_CH6_PIN A5

// ESC Module
#define ESC_FL_PIN 2
#define ESC_FR_PIN 3
#define ESC_BL_PIN 6
#define ESC_BR_PIN 5

// PWM Constants
// these are the duration of PWM pulses in ms
#define PWM_MIN 1000
#define PWM_MAX 2000

// IMU Module
#define IMU_INT_PIN 35
#define IMU_AD0_PIN LOW
#define IMU_DMP_HLT false // Should the program wait for serial input to calibrate DMP

#define IMU_X_ACCEL   286
#define IMU_Y_ACCEL -4546
#define IMU_Z_ACCEL  1008
#define IMU_X_GYRO     66
#define IMU_Y_GYRO      5
#define IMU_Z_GYRO     27

#endif