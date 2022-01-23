/* Main Robot Code */

#include<EnableInterrupt.h>
#include<Servo.h>

#define SERIAL_PORT_SPEED 9600
#define RC_NUM_CHANNELS	6

#define RC_CH1 0
#define RC_CH2 1
#define RC_CH3 2
#define RC_CH4 3
#define RC_CH5 4
#define RC_CH6 5

#define RC_CH1_INPUT A5
#define RC_CH2_INPUT A4
#define RC_CH3_INPUT A3
#define RC_CH4_INPUT A2
#define RC_CH5_INPUT A1
#define RC_CH6_INPUT A0

#define ESC_FL_PIN 2
#define ESC_FR_PIN 3
#define ESC_BL_PIN 6
#define ESC_BR_PIN 5

uint16_t rc_values[RC_NUM_CHANNELS];
uint32_t rc_start[RC_NUM_CHANNELS];
volatile uint16_t rc_shared[RC_NUM_CHANNELS];

Servo esc_fl;
Servo esc_fr;
Servo esc_bl;
Servo esc_br;

int printval;

void rc_read_values() {
	noInterrupts();
	memcpy(rc_values, (const void *)rc_shared, sizeof(rc_shared));
	interrupts();
}

void calc_input(uint8_t channel, uint8_t input_pin) {
	if (digitalRead(input_pin) == HIGH) {
		rc_start[channel] = micros();
	} else {
		uint16_t rc_compare = (uint16_t)(micros() - rc_start[channel]);
		rc_shared[channel] = rc_compare;
	}
}

void calc_ch1() { calc_input(RC_CH1, RC_CH1_INPUT); }
void calc_ch2() { calc_input(RC_CH2, RC_CH2_INPUT); }
void calc_ch3() { calc_input(RC_CH3, RC_CH3_INPUT); }
void calc_ch4() { calc_input(RC_CH4, RC_CH4_INPUT); }
void calc_ch5() { calc_input(RC_CH5, RC_CH5_INPUT); }
void calc_ch6() { calc_input(RC_CH6, RC_CH6_INPUT); }

void setup() {
	Serial.begin(SERIAL_PORT_SPEED);

	pinMode(RC_CH1_INPUT, INPUT);
	pinMode(RC_CH2_INPUT, INPUT);
	pinMode(RC_CH3_INPUT, INPUT);
	pinMode(RC_CH4_INPUT, INPUT);
	pinMode(RC_CH5_INPUT, INPUT);
	pinMode(RC_CH6_INPUT, INPUT);
	
	enableInterrupt(RC_CH1_INPUT, calc_ch1, CHANGE);
	enableInterrupt(RC_CH2_INPUT, calc_ch2, CHANGE);
	enableInterrupt(RC_CH3_INPUT, calc_ch3, CHANGE);
	enableInterrupt(RC_CH4_INPUT, calc_ch4, CHANGE);
	enableInterrupt(RC_CH5_INPUT, calc_ch5, CHANGE);
	enableInterrupt(RC_CH6_INPUT, calc_ch6, CHANGE);

	esc_fl.attach(ESC_FL_PIN, 1000, 2000);
	esc_fr.attach(ESC_FR_PIN, 1000, 2000);
	esc_bl.attach(ESC_BL_PIN, 1000, 2000);
	esc_br.attach(ESC_BR_PIN, 1000, 2000);

    printval = 0;
}

void loop() {
	rc_read_values();

    if(printval >= 10) {
        // RIGHT STICK LEFT/RIGHT
        Serial.print("CH1:"); Serial.print(map(rc_values[RC_CH1], 1000, 2000, -100, 100)); Serial.print("\t");
        // RIGHT STICK UP/DOWN
        Serial.print("CH2:"); Serial.print(map(rc_values[RC_CH2], 1000, 2000, -100, 100)); Serial.print("\t");
        // LEFT STICK UP/DOWN
        Serial.print("CH3:"); Serial.print(map(rc_values[RC_CH3], 1000, 2000, -100, 100)); Serial.print("\t");
        // LEFT STICK LEFT/RIGHT
        Serial.print("CH4:"); Serial.print(map(rc_values[RC_CH4], 1000, 2000, -100, 100)); Serial.print("\t");
        // LEFT KNOB
        Serial.print("CH5:"); Serial.print(map(rc_values[RC_CH5], 1000, 2000, -100, 100)); Serial.print("\t");
        // RIGHT KNOB
        Serial.print("CH6:"); Serial.println(map(rc_values[RC_CH6], 1000, 2000, -100, 100));

        printval = 0;
    }

    int powerLevel = map(rc_values[RC_CH3], 1000, 2000, 0, 180);
    Serial.print("Power Level: "); Serial.println(powerLevel);

    esc_fl.write(powerLevel);
    esc_fr.write(powerLevel);
    esc_bl.write(powerLevel);
    esc_br.write(powerLevel);

    ++printval;
	delay(20);
}