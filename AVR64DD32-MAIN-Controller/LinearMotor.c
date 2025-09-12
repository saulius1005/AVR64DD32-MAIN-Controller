/*
 * LinearMotor.c
 *
 * Created: 2025-09-09 14:20:10
 *  Author: Saulius
 */ 
#include "Settings.h"
#include "LinearMotorVar.h"

void LinearMotor_enable(){ //turn on TLE9201SG
	if(LinearMotor.alreadyEnabled == false){
		PORTD.OUTCLR = PIN2_bm;  // DIS=0
		_delay_ms(10);
		LinearMotor.alreadyEnabled = true;
		LinearMotor.alreadyDisabled = false;
	}
}

void LinearMotor_disable(){ //turn off TLE9201SG
	if(LinearMotor.alreadyDisabled == false){
		PORTD.OUTSET = PIN2_bm;  // DIS=1
		_delay_ms(10);
		LinearMotor.alreadyDisabled = true;
		LinearMotor.alreadyEnabled = false;
	}
}

void LinearMotor_start(){ //starting pwm signal generation
	if(LinearMotor.alreadyStarted == false){		
		TCA0.SPLIT.CTRLB |= TCA_SPLIT_HCMP0EN_bm; //connecting TCA to PD3
		TCA0.SPLIT.CTRLA |= TCA_SPLIT_ENABLE_bm; //turn on TCA back
		LinearMotor.alreadyStarted = true;
		LinearMotor.alreadyStoped = false;
	}

}

void LinearMotor_stop(){
	if(LinearMotor.alreadyStoped == false){ //stoping pwm signal generation
		TCA0.SPLIT.CTRLB &= ~(TCA_SPLIT_HCMP0EN_bm); //disconecting TCA from PD3
		TCA0.SPLIT.CTRLA &= ~TCA_SPLIT_ENABLE_bm;  // turn off TCA
		PORTD.OUTCLR = PIN3_bm; //ensure PWM low level
		_delay_ms(500); //preventing from error flag- 500mS of free spinning

		LinearMotor.alreadyStoped = true;
		LinearMotor.alreadyStarted = false;
	}

}

void LinearMotor_set_direction(bool dir)
{
    if (dir != LinearMotor.lastDirection)  // if direction change (single time per cycle)
    {
		LinearMotor_stop();
		if(dir)
            PORTD.OUTSET = PIN5_bm;   // UP
		else
            PORTD.OUTCLR = PIN5_bm;   // DOWN
		LinearMotor_start();
        LinearMotor.lastDirection = dir;
    }
}

void LinearMotor_init(){
	TCA0_init_linear_PWM(20000, 50);

	PORTD.OUTCLR = PIN3_bm; //set PWM signal low
	PORTD.OUTSET = PIN2_bm; //set output disabled for TLE9201SG
};


