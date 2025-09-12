/*
 * StepperMotor.h
 *
 * Created: 2025-09-11 10:30:32
 *  Author: Saulius
 */ 


#ifndef STEPPERMOTOR_H_
#define STEPPERMOTOR_H_


typedef struct {
	bool lastDirection;
	bool alreadyStarted;
	bool alreadyStoped;
	bool alreadyEnabled;
	bool alreadyDisabled;
} HBS86;

extern HBS86 StepperMotor;


#endif /* STEPPERMOTOR_H_ */