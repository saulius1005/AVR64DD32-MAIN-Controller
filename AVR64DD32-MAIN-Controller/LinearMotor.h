/*
 * LinearMotor.h
 *
 * Created: 2025-09-09 14:37:43
 *  Author: Saulius
 */ 


#ifndef LINEARMOTOR_H_
#define LINEARMOTOR_H_

#define LinearMotor_Voltage_Compensation_koef 0.987755 //24,2 Actual measured voltage and calculated 24,5

typedef struct {
	bool lastDirection;
	bool alreadyStarted;
	bool alreadyStoped;
	bool alreadyEnabled;
	bool alreadyDisabled;
	uint16_t measuredVoltage;
	int16_t measuredCurrent;
	uint8_t stuckCount;
	uint8_t noChangeCount;
} TLE9201SG;

extern TLE9201SG LinearMotor;

#endif /* LINEARMOTOR_H_ */