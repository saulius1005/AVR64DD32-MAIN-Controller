/*
 * LinearMotor.h
 *
 * Created: 2025-09-09 14:37:43
 *  Author: Saulius
 */ 


#ifndef LINEARMOTOR_H_
#define LINEARMOTOR_H_

#define Angle_Backlash 5
#define MAX_Elevation 95

#define MAX_NO_CHANGE 3  // kiek bandymø toleruojam, jei kampas nekinta

typedef struct {
	bool lastDirection;
	bool newDirection;
	bool angleError;
} TLE9201SG;

extern TLE9201SG LinearMotor;

#endif /* LINEARMOTOR_H_ */