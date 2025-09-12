/*
 * StepperMotor.h
 *
 * Created: 2025-09-11 10:30:32
 *  Author: Saulius
 */ 


#ifndef STEPPERMOTOR_H_
#define STEPPERMOTOR_H_

#define Stepper_Voltage_Compensation_koef 1.05 //59,62V Actual measured voltage and calculated 56,7V

typedef struct {
	bool lastDirection;
	bool alreadyStarted;
	bool alreadyStoped;
	bool alreadyEnabled;
	bool alreadyDisabled;
} HBS86;

extern HBS86 StepperMotor;


#endif /* STEPPERMOTOR_H_ */