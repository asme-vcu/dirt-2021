/* Main Robot Code */
#include"consts.h"
#include"rc.h"
#include"imu.h"
#include<Servo.h>

RC* rc;
IMU* imu;

Servo esc_fl;
Servo esc_fr;
Servo esc_bl;
Servo esc_br;

uint32_t debug_timer;

void setup() {
	Serial.begin(SERIAL_PORT_SPEED);

    rc = RC::getInstance();
    rc->setup();

    imu = IMU::getInstance();
    imu->setup();

	esc_fl.attach(ESC_FL_PIN, PWM_MIN, PWM_MAX);
	esc_fr.attach(ESC_FR_PIN, PWM_MIN, PWM_MAX);
	esc_bl.attach(ESC_BL_PIN, PWM_MIN, PWM_MAX);
	esc_br.attach(ESC_BR_PIN, PWM_MIN, PWM_MAX);

    debug_timer = millis();
}

void loop() {
    rc->run();
    imu->run();

    int powerLevel = rc->getLeftStickY();
    esc_fl.writeMicroseconds(powerLevel);
    esc_fr.writeMicroseconds(powerLevel);
    esc_bl.writeMicroseconds(powerLevel);
    esc_br.writeMicroseconds(powerLevel);

#if DEBUG_ENABLED
    if(millis() >= debug_timer + DEBUG_INTERVAL) {
        rc->printDebug();
        imu->printDebug();
        Serial.print("Power Level: "); Serial.println(powerLevel);

        debug_timer = millis();
    }
#endif
}
