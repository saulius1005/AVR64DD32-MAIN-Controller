/*
 * LinearMotorVar.h
 *
 * Created: 2025-09-09 14:37:56
 *  Author: Saulius
 */ 


#ifndef LINEARMOTORVAR_H_
#define LINEARMOTORVAR_H_

#define LinearMotor_Voltage_Compensation_koef 0.987755 //24,2 Actual measured voltage and calculated 24,5

TLE9201SG LinearMotor = {
	.lastDirection = false,
	.alreadyStarted = false,
	.alreadyStoped = false,
	.alreadyEnabled = false,
	.alreadyDisabled = false,
	.measuredVoltage = 0,
	.measuredCurrent = 0
};

#endif /* LINEARMOTORVAR_H_ */