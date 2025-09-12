/*
 * LinearMotorVar.h
 *
 * Created: 2025-09-09 14:37:56
 *  Author: Saulius
 */ 


#ifndef LINEARMOTORVAR_H_
#define LINEARMOTORVAR_H_

TLE9201SG LinearMotor = {
	.lastDirection = false,
	.newDirection = false,
	.angleError = false,
	.targetReached = false,
	.noChangeCount = 0,
	.lastElevation = 0
};

#endif /* LINEARMOTORVAR_H_ */