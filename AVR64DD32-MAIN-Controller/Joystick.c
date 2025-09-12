/*
 * Joystick.c
 *
 * Created: 2025-09-08 12:58:23
 *  Author: Saulius
 */ 
#include "Settings.h"
#include "JoystickVar.h"

uint8_t ReadButton(){
	return !(PORTA.IN & PIN1_bm);
}


void ReadJoystickValues(){
	ADC0_SetupJoystick(Joystick_X_axis_CH);
	Joystick.X_Axis = ((int16_t)ADC0_read()-2048)/Joystick_steps; // 5 steps total: -2,-1,0,1,2 (4096/1000 = 4,096)
	ADC0_SetupJoystick(Joystick_Y_axis_CH);
	Joystick.Y_Axis = ((int16_t)ADC0_read()-2048)/Joystick_steps;
	Joystick.Button = ReadButton();
}
