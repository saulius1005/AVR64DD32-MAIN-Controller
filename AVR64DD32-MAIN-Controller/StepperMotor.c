/*
 * StepperMotor.c
 *
 * Created: 2025-09-11 10:29:21
 *  Author: Saulius
 */ 
#include "Settings.h"


// -------------------------
// Stepper Enable / Disable
// -------------------------
void Stepper_enable() {
	PORTF.OUTCLR = PIN1_bm; // aktyvus LOW
}

void Stepper_disable() {
	PORTF.OUTSET = PIN1_bm; // HIGH = inactive
}

// -------------------------
// Stepper Direction
// -------------------------
void Stepper_set_direction(uint8_t dir) {
	if (dir)
	PORTF.OUTSET = PIN3_bm;
	else
	PORTF.OUTCLR = PIN3_bm;
}

// -------------------------
// Stepper Start / Stop
// -------------------------
void Stepper_start() {
	// Ájungti WOC PF2
	TCD0.FAULTCTRL |= (TCD_CMPAEN_bm | TCD_CMPBEN_bm | TCD_CMPCEN_bm);

	// Ájungti TCD counter
	TCD0.CTRLA |= TCD_ENABLE_bm;

	// PF2 dabar generuoja STEP signalus
}

void Stepper_stop() {
	// Sustabdyti TCD counter
	TCD0.CTRLA &= ~TCD_ENABLE_bm;

	// Atjungti WOC PF2
	TCD0.FAULTCTRL &= ~(TCD_CMPAEN_bm | TCD_CMPBEN_bm | TCD_CMPCEN_bm);

	// Uþtikrinti, kad PF2 LOW (driver idle)
	PORTF.OUTCLR = PIN2_bm;
}

// -------------------------
// PWM Update (Frequency / Duty Cycle)
// -------------------------
void Stepper_set_frequency(uint32_t target_freq, uint8_t duty_cycle) {
	uint16_t cmpbclr = (F_CPU / (4 * target_freq * 2)) - 1;
	uint16_t cmpaset = (uint16_t)(cmpbclr * (duty_cycle / 100.0));
	uint16_t cmpbset = cmpbclr - cmpaset;

	TCD0.CMPBCLR = cmpbclr;
	TCD0.CMPBSET = cmpbset;
	TCD0.CMPASET = cmpaset;
}

// -------------------------
// Init function
// -------------------------
void Stepper_init() {
	// Ájungiam WOC PF2
	TCD0_init();

	// Default PWM
	Stepper_set_frequency(40000, 50); // 40kHz, 50% duty

	// Set idle states
	PORTF.OUTCLR = PIN2_bm;
	PORTF.OUTSET = PIN1_bm; // disable
	PORTF.OUTCLR = PIN3_bm; // default direction
}