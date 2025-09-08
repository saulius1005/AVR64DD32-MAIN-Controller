/*
 * Joystick.h
 *
 * Created: 2025-09-08 12:58:50
 *  Author: Saulius
 */ 


#ifndef JOYSTICK_H_
#define JOYSTICK_H_

#define Joystick_X_axis_CH ADC_MUXPOS_AIN29_gc //dependet  from GPIO.c settings
#define Joystick_Y_axis_CH ADC_MUXPOS_AIN30_gc //dependet  from GPIO.c settings

typedef struct {
	uint16_t X_Axis;
	uint16_t Y_Axis;
	uint8_t Button;
} ADCJoy;

extern ADCJoy Joystick;

#endif /* JOYSTICK_H_ */