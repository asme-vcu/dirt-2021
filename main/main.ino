/* Main Robot Code */

#include"consts.h"
#include"rc.h"

#include<Servo.h>

RC* rc;

Servo esc_fl;
Servo esc_fr;
Servo esc_bl;
Servo esc_br;

int debug_timer;

void setup() {
	Serial.begin(SERIAL_PORT_SPEED);

    rc = RC::getInstance();
    rc->setup();

	esc_fl.attach(ESC_FL_PIN, PWM_MIN, PWM_MAX);
	esc_fr.attach(ESC_FR_PIN, PWM_MIN, PWM_MAX);
	esc_bl.attach(ESC_BL_PIN, PWM_MIN, PWM_MAX);
	esc_br.attach(ESC_BR_PIN, PWM_MIN, PWM_MAX);

    debug_timer = millis();
}

void loop() {
    rc->run();

    int powerLevel = rc->getLeftStickY();
    esc_fl.writeMicroseconds(powerLevel);
    esc_fr.writeMicroseconds(powerLevel);
    esc_bl.writeMicroseconds(powerLevel);
    esc_br.writeMicroseconds(powerLevel);

    if(millis() >= debug_timer + DEBUG_INTERVAL) {
        rc->printDebug();
        Serial.print("Power Level: "); Serial.println(powerLevel);

        debug_timer = millis();
    }
}