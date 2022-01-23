/* RC Transmission Submodule Implementation */
#include"rc.h"
#include"consts.h"
#include<EnableInterrupt.h>

#define RC_CH1 0 // RIGHT STICK LEFT/RIGHT
#define RC_CH2 1 // RIGHT STICK UP/DOWN
#define RC_CH3 2 // LEFT STICK UP/DOWN
#define RC_CH4 3 // LEFT STICK LEFT/RIGHT
#define RC_CH5 4 // LEFT KNOB
#define RC_CH6 5 // RIGHT KNOB

uint16_t RC::rc_values[RC_NUM_CHANNELS]          = {0};
volatile uint16_t RC::rc_shared[RC_NUM_CHANNELS] = {0};
uint32_t RC::rc_timer[RC_NUM_CHANNELS]           = {0};
RC* RC::instance = new RC;

// Pause interrupts and copy current RC values to non-volatile memory
void RC::read_rc_values() {
    noInterrupts();
    memcpy(rc_values, (const void*)rc_shared, sizeof(rc_shared));
    interrupts();
}

// Calculate input based on pulse-width from timers
void RC::calc_input(uint8_t channel, uint8_t input_pin) {
	if (digitalRead(input_pin) == HIGH) {
		rc_timer[channel] = micros();
	} else {
		uint16_t rc_compare = (uint16_t)(micros() - rc_timer[channel]);
		rc_shared[channel] = rc_compare;
	}
}

// Interrupt handlers for each channel
void RC::ch1_interrupt() { calc_input(RC_CH1, RC_CH1_PIN); }
void RC::ch2_interrupt() { calc_input(RC_CH2, RC_CH2_PIN); }
void RC::ch3_interrupt() { calc_input(RC_CH3, RC_CH3_PIN); }
void RC::ch4_interrupt() { calc_input(RC_CH4, RC_CH4_PIN); }
void RC::ch5_interrupt() { calc_input(RC_CH5, RC_CH5_PIN); }
void RC::ch6_interrupt() { calc_input(RC_CH6, RC_CH6_PIN); }

// Main module setup
void RC::setup() {
    pinMode(RC_CH1_PIN, INPUT);
    pinMode(RC_CH2_PIN, INPUT);
    pinMode(RC_CH3_PIN, INPUT);
    pinMode(RC_CH4_PIN, INPUT);
    pinMode(RC_CH5_PIN, INPUT);
    pinMode(RC_CH6_PIN, INPUT);

    enableInterrupt(RC_CH1_PIN, ch1_interrupt, CHANGE);
    enableInterrupt(RC_CH2_PIN, ch2_interrupt, CHANGE);
    enableInterrupt(RC_CH3_PIN, ch3_interrupt, CHANGE);
    enableInterrupt(RC_CH4_PIN, ch4_interrupt, CHANGE);
    enableInterrupt(RC_CH5_PIN, ch5_interrupt, CHANGE);
    enableInterrupt(RC_CH6_PIN, ch6_interrupt, CHANGE);
}

// Main module run-loop
void RC::run() {
    read_rc_values();
}

// Constructor
RC::RC() {}

// Retrieve the instance of this class (there can only be one!!)
RC* RC::getInstance() {
    if(!instance)
        instance = new RC;
    
    return instance;
}

void RC::printDebug() {
    Serial.print("CH1:"); Serial.print(map(rc_values[RC_CH1], PWM_MIN, PWM_MAX, -100, 100)); Serial.print("\t");
    Serial.print("CH2:"); Serial.print(map(rc_values[RC_CH2], PWM_MIN, PWM_MAX, -100, 100)); Serial.print("\t");
    Serial.print("CH3:"); Serial.print(map(rc_values[RC_CH3], PWM_MIN, PWM_MAX, -100, 100)); Serial.print("\t");
    Serial.print("CH4:"); Serial.print(map(rc_values[RC_CH4], PWM_MIN, PWM_MAX, -100, 100)); Serial.print("\t");
    Serial.print("CH5:"); Serial.print(map(rc_values[RC_CH5], PWM_MIN, PWM_MAX, -100, 100)); Serial.print("\t");
    Serial.print("CH6:"); Serial.print(map(rc_values[RC_CH6], PWM_MIN, PWM_MAX, -100, 100)); Serial.print("\n");
}

uint16_t RC::getLeftStickX()  { return rc_values[RC_CH4]; }
uint16_t RC::getLeftStickY()  { return rc_values[RC_CH3]; }
uint16_t RC::getRightStickX() { return rc_values[RC_CH1]; }
uint16_t RC::getRightStickY() { return rc_values[RC_CH2]; }
uint16_t RC::getLeftKnob()    { return rc_values[RC_CH5]; }
uint16_t RC::getRightKnob()   { return rc_values[RC_CH6]; }
