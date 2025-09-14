/*
 * StepperMotor.c
 *
 * Created: 2025-09-11 10:29:21
 *  Author: Saulius
 */ 
#include "Settings.h"
#include "StepperMotorVar.h"


// -------------------------
// Stepper Enable / Disable
// -------------------------
void Stepper_enable() {
	if(StepperMotor.alreadyEnabled == false){
		PORTF.OUTCLR = PIN1_bm; // aktyvus LOW
		_delay_ms(10);
		StepperMotor.alreadyEnabled = true;
		StepperMotor.alreadyDisabled = false;
	}
}

void Stepper_disable() {
	if(StepperMotor.alreadyDisabled == false){
		PORTF.OUTSET = PIN1_bm; // HIGH = inactive
		_delay_ms(10);
		StepperMotor.alreadyDisabled = true;
		StepperMotor.alreadyEnabled = false;
	}
}

// -------------------------
// Stepper Start / Stop
// -------------------------
void Stepper_start() {
	if(StepperMotor.alreadyStarted == false){
		TCD0.FAULTCTRL |= (TCD_CMPAEN_bm | TCD_CMPBEN_bm | TCD_CMPCEN_bm);
		TCD0.CTRLA |= TCD_ENABLE_bm;
		StepperMotor.alreadyStarted = true;
		StepperMotor.alreadyStoped = false;
	}
}


void Stepper_stop() {
	if(StepperMotor.alreadyStoped == false){
		TCD0.CTRLA &= ~TCD_ENABLE_bm;
		TCD0.FAULTCTRL &= ~(TCD_CMPAEN_bm | TCD_CMPBEN_bm | TCD_CMPCEN_bm); //disconnecting PF2 from TCD counter
		PORTF.OUTCLR = PIN2_bm;
		StepperMotor.alreadyStoped = true;
		StepperMotor.alreadyStarted = false;
	}
}

// -------------------------
// Stepper Direction
// -------------------------
void Stepper_set_direction(bool dir) {
	if (dir != StepperMotor.lastDirection)  // if direction change (single time per cycle)
	{
		if (dir)
			PORTF.OUTSET = PIN3_bm;
		else
			PORTF.OUTCLR = PIN3_bm;
		StepperMotor.lastDirection = dir;
	}
}

// -------------------------
// Init function
// -------------------------
void Stepper_init() {

	// Default PWM
	TCD0_init_stepper_PWM(51200, 50); // 51.2kHz, 50% duty

	// Set idle states
	PORTF.OUTCLR = PIN2_bm; // pulse low
	PORTF.OUTSET = PIN1_bm; // disable
	PORTF.OUTCLR = PIN3_bm; // default direction
}

bool Read_Stepper_PEND(){ // true if position reached
	return !(PORTF.IN & PIN5_bm);
}

bool Read_Stepper_ALM(){ // true if driver has a error (overheat, stepepr stuck and so on)
	return !(PORTF.IN & PIN4_bm);
}

uint16_t Read_Stepper_Voltage(){
	ADC0_SetupStepper(0);
	return (ADC0_read() * 0.1775) * Stepper_Voltage_Compensation_koef;
}

int16_t Read_Stepper_Current(){
	ADC0_SetupStepper(1);
	return ((int16_t)ADC0_read() - (int16_t)Read_MCU_Voltge())/4;
}