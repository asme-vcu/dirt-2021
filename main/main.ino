/* Main Robot Code */
#include"consts.h"
#include"rc.h"
//#include"imu.h"
#include<Servo.h>

RC rc;
//IMU* imu;

Servo esc_fl;
Servo esc_fr;
Servo esc_bl;
Servo esc_br;

int power_calibrate;
uint32_t debug_timer;

void setup() {
	Serial.begin(SERIAL_PORT_SPEED);
    Serial.println("Goodbye cruel world ;(");

    rc = RC();
    rc.setup();

    //imu = IMU::getInstance();
    //imu->setup();

	esc_fl.attach(ESC_FL_PIN, PWM_MIN, PWM_MAX);
	esc_fr.attach(ESC_FR_PIN, PWM_MIN, PWM_MAX);
	esc_bl.attach(ESC_BL_PIN, PWM_MIN, PWM_MAX);
	esc_br.attach(ESC_BR_PIN, PWM_MIN, PWM_MAX);

    debug_timer = millis();

    /*power_calibrate = 0;
    for(int i = 0; i < 100; i++) {
        rc->run();
        int power = rc->getRightStickY();
        if(power >= PWM_MIN && power <= PWM_MAX) {
            power_calibrate += power;
        } else i--;
        delay(200);
    }
    power_calibrate /= 100;*/
}

void loop() {
    rc.run();
    //imu->run();

    int powerLevel = rc.getRightStickY();
    esc_fl.writeMicroseconds(powerLevel);
    esc_fr.writeMicroseconds(powerLevel);
    esc_bl.writeMicroseconds(powerLevel);
    esc_br.writeMicroseconds(powerLevel);

#if DEBUG_ENABLED
    if(millis() >= debug_timer + DEBUG_INTERVAL) {
        rc.printDebug();
        //imu->printDebug();
        Serial.print("Power Level: "); Serial.println(powerLevel);

        debug_timer = millis();
    }
#endif
}
