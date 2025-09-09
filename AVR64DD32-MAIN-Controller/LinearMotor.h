/*
 * LinearMotor.h
 *
 * Created: 2025-09-09 14:37:43
 *  Author: Saulius
 */ 


#ifndef LINEARMOTOR_H_
#define LINEARMOTOR_H_

typedef struct {
	bool lastDirection;
	bool newDirection;
} TLE9201SG;

extern TLE9201SG LinearMotor;

#endif /* LINEARMOTOR_H_ */