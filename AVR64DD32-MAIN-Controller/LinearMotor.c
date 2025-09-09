/*
 * LinearMotor.c
 *
 * Created: 2025-09-09 14:20:10
 *  Author: Saulius
 */ 
#include "Settings.h"
#include "LinearMotorVar.h"

void Motor_SetDirection()
{
    if (LinearMotor.newDirection != LinearMotor.lastDirection)  // if direction change (single time per cycle)
    {
	   TCA0.SPLIT.CTRLB &= ~(TCA_SPLIT_HCMP0EN_bm); //disconecting TCA from PD3
       TCA0.SPLIT.CTRLA &= ~TCA_SPLIT_ENABLE_bm;  // turn off TCA
	   PORTD.OUTCLR = PIN3_bm; //ensure PWM low level
	   _delay_ms(500); //preventing from error flag- 500mS of free spinning
       PORTD.OUTSET = PIN2_bm;  // DIS=1
	   _delay_ms(10);
        if (LinearMotor.newDirection) {
            PORTD.OUTSET = PIN5_bm;   // UP
        } else {
            PORTD.OUTCLR = PIN5_bm;   // DOWN
        }
        LinearMotor.lastDirection = LinearMotor.newDirection;
        PORTD.OUTCLR = PIN2_bm;  // DIS=0
		_delay_ms(10);
		TCA0.SPLIT.CTRLB |= TCA_SPLIT_HCMP0EN_bm; //connecting TCA to PD3
        TCA0.SPLIT.CTRLA |= TCA_SPLIT_ENABLE_bm; //turn on TCA back
    }
}