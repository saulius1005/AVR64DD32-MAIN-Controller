/*
 * Joystick.c
 *
 * Created: 2025-09-08 12:58:23
 *  Author: Saulius
 */ 
#include "Settings.h"
#include "JoystickVar.h"

uint8_t ReadButton(){
	return (PORTA.IN & PIN1_bm) == 0 ? 1 : 0;
}


void ReadJoystickValues(){
	ADC0_SetupJoystick(Joystick_X_axis_CH);
	Joystick.X_Axis = ADC0_read();
	ADC0_SetupJoystick(Joystick_Y_axis_CH);
	Joystick.Y_Axis = ADC0_read();
	Joystick.Button = ReadButton();
}
