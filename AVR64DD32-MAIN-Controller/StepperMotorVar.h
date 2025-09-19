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
	.alreadyDisabled = false,
	.measuredVoltage = 0,
	.measuredCurrent = 0,
	.stuckCount = 0,
	.noChangeCount = 0
};


#endif /* STEPPERMOTORVAR_H_ */