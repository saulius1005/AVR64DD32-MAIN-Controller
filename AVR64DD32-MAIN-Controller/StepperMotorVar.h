/*
 * StepperMotorVar.h
 *
 * Created: 2025-09-11 10:30:53
 *  Author: Saulius
 */ 


#ifndef STEPPERMOTORVAR_H_
#define STEPPERMOTORVAR_H_


HBS86 StepperMotor = {
	.lastDirection = false,
	.alreadyStarted = false,
	.alreadyStoped = false,
	.alreadyEnabled = false,
	.alreadyDisabled = false
};


#endif /* STEPPERMOTORVAR_H_ */