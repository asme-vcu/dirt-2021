/* Main Robot Code */

#include"consts.h"
#include"rc.h"

#include<Servo.h>

RC* rc;

Servo esc_fl;
Servo esc_fr;
Servo esc_bl;
Servo esc_br;

int debug_interval;

void setup() {
	Serial.begin(SERIAL_PORT_SPEED);

    rc = RC::getInstance();
    rc->setup();

	esc_fl.attach(ESC_FL_PIN, 1000, 2000);
	esc_fr.attach(ESC_FR_PIN, 1000, 2000);
	esc_bl.attach(ESC_BL_PIN, 1000, 2000);
	esc_br.attach(ESC_BR_PIN, 1000, 2000);

    debug_interval = 0;
}

void loop() {
    rc->run();

    if(debug_interval >= 10) {
        rc->printDebug();

        debug_interval = 0;
    }

    int powerLevel = map(rc->getLeftStickY(), 1000, 2000, 0, 180);
    Serial.print("Power Level: "); Serial.println(powerLevel);

    esc_fl.write(powerLevel);
    esc_fr.write(powerLevel);
    esc_bl.write(powerLevel);
    esc_br.write(powerLevel);

    ++debug_interval;
	delay(20);
}