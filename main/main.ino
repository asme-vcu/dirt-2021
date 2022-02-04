/* Main Robot Code */
#include"consts.h"
#include"rc.h"
#include"imu.h"
#include<Servo.h>

RC rc;
IMU imu;

Servo esc_l;
Servo esc_r;

uint32_t debug_timer;

void setup() {
	Serial.begin(SERIAL_PORT_SPEED);
    while(!Serial) delay(10);

    rc = RC();
    rc.setup();

    imu = IMU();
    imu.setup();

	esc_l.attach(ESC_L_PIN, PWM_MIN, PWM_MAX);
	esc_r.attach(ESC_R_PIN, PWM_MIN, PWM_MAX);

    debug_timer = millis();

    pinMode(LED_HALT, OUTPUT);
    pinMode(LED_NOSIG, OUTPUT);
}

void loop() {
    rc.run();
    imu.run();

    bool halt = false;

    int powerLevel = constrain(rc.getRightStickY(), 1000, 2000);

    // Get killswitch
    if(rc.getSwitchA() > 1500) {
        halt = true;
        digitalWrite(LED_HALT, HIGH);
    } else {
        digitalWrite(LED_HALT, LOW);
    }

    // Get connection status
    if(rc.isDisconnected()) {
        halt = true;
        digitalWrite(LED_NOSIG, HIGH);
    } else {
        digitalWrite(LED_NOSIG, LOW);
    }

    // means turn off motor (bidirectional between 1000 and 2000 ms)
    if(halt) powerLevel = 1500;

    esc_l.writeMicroseconds(powerLevel);
    esc_r.writeMicroseconds(powerLevel);

#if DEBUG_ENABLED
    if(millis() >= debug_timer + DEBUG_INTERVAL) {
        rc.printDebug();
        imu.printDebug();
        Serial.print("Power Level: "); Serial.println(powerLevel);

        debug_timer = millis();
    }
#endif
}
