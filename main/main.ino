/* Main Robot Code */
#include"consts.h"
#include"rc.h"
#include"imu.h"
#include"drive.h"
#include"led_controller.h"

LEDController leds;
RC rc(leds);
IMU imu(leds);
Drive drive(imu, rc);

uint32_t debug_timer;

void setup() {
	Serial.begin(SERIAL_PORT_SPEED);
    while(!Serial) delay(10);

    leds.setup();
    rc.setup();
    imu.setup();
    drive.setup();

    debug_timer = millis();
}

void loop() {
    leds.run();
    rc.run();
    imu.run();
    drive.run();

#if DEBUG_ENABLED
    if(millis() >= debug_timer + DEBUG_INTERVAL) {
        leds.printDebug();
        rc.printDebug();
        imu.printDebug();
        drive.printDebug();

        debug_timer = millis();
    }
#endif
}
