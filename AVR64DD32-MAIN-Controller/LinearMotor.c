/*
 * LinearMotor.c
 *
 * Created: 2025-09-09 14:20:10
 *  Author: Saulius
 */ 
#include "Settings.h"
#include "LinearMotorVar.h"

void Motor_Stop(){
	TCA0.SPLIT.CTRLB &= ~(TCA_SPLIT_HCMP0EN_bm); //disconecting TCA from PD3
	TCA0.SPLIT.CTRLA &= ~TCA_SPLIT_ENABLE_bm;  // turn off TCA
	PORTD.OUTCLR = PIN3_bm; //ensure PWM low level
	_delay_ms(500); //preventing from error flag- 500mS of free spinning
	PORTD.OUTSET = PIN2_bm;  // DIS=1
	_delay_ms(10);
}

void Motor_Start(){
	PORTD.OUTCLR = PIN2_bm;  // DIS=0
	_delay_ms(10);
	TCA0.SPLIT.CTRLB |= TCA_SPLIT_HCMP0EN_bm; //connecting TCA to PD3
	TCA0.SPLIT.CTRLA |= TCA_SPLIT_ENABLE_bm; //turn on TCA back
}

void Motor_SetDirection()
{
    if (LinearMotor.newDirection != LinearMotor.lastDirection)  // if direction change (single time per cycle)
    {
		Motor_Stop();
        if (LinearMotor.newDirection) {
            PORTD.OUTSET = PIN5_bm;   // UP
        } else {
            PORTD.OUTCLR = PIN5_bm;   // DOWN
        }
        LinearMotor.lastDirection = LinearMotor.newDirection;
		Motor_Start();
    }
}



void Motor_SetTarget(uint8_t angle) {
	// Tikrinam, ar jau esam reikiamame intervale
	if ( (SensorData.Elevation > (angle + Angle_Backlash) || SensorData.Elevation < (angle - Angle_Backlash)) && LinearMotor.angleError == false ){
		uint8_t noChangeCount = 0;
		uint16_t lastElevation = SensorData.HPElevation; //high precision elevation data for sensor stuck error diagnosis

		while (SensorData.Elevation != angle)
		{
			FOReceiver(); // atnaujinam jutiklio duomenis
			screen_write_formatted_text("%3d", 0, ALIGN_CENTER, SensorData.Elevation); //debug
			screen_write_formatted_text("%d", 1, ALIGN_CENTER, LinearMotor.angleError); //debug
			_delay_ms(500);
			if (SensorData.Elevation < (angle - Angle_Backlash)) {
				LinearMotor.newDirection = true;   // sukti á prieká
			}
			else if (SensorData.Elevation > (angle + Angle_Backlash)) {
				LinearMotor.newDirection = false;  // sukti atgal
			}
			Motor_SetDirection();   // nustatom kryptá
			Motor_Start();            // paleidþiam PWM
			// tikrinam, ar kampas keièiasi
			if (SensorData.HPElevation == lastElevation) {
				noChangeCount++;
				if (noChangeCount >= MAX_NO_CHANGE) {
					Motor_Stop();
					LinearMotor.angleError = true;
					break;
				}
				} else {
				noChangeCount = 0;  // judëjimas ávyko ? resetinam
			}

			lastElevation = SensorData.HPElevation;
		}
		Motor_Stop(); // <-- labai svarbu! kai pasiekiam kampà, motoras turi bûti iðjungtas
	}
	else if (SensorData.Elevation + Angle_Backlash > MAX_Elevation){
		Motor_Stop();
		LinearMotor.angleError = true;
	}
	else{
		LinearMotor.angleError = false; // reset error if angle is reached
	}
}

void Motor_SetTarget_NB(uint8_t angle) {
    static uint8_t noChangeCount = 0;
    static uint16_t lastElevation = 0;
    static bool targetReached = false; // ar pasiektas tikslus kampas

    // Resetinam targetReached, jei kampas iðeina uþ ±backlash ribos
    if (SensorData.Elevation < (angle - Angle_Backlash) || 
        SensorData.Elevation > (angle + Angle_Backlash)) 
    {
        targetReached = false;
    }

    if (!targetReached) {
        // Nustatom kryptá visada link tikslo
        if (SensorData.Elevation < angle) {
            LinearMotor.newDirection = true;   // á prieká
        } else if (SensorData.Elevation > angle) {
            LinearMotor.newDirection = false;  // atgal
        }

        Motor_SetDirection();
        Motor_Start();

        // stuck detection tik jei motoras turi judëti
        if (SensorData.HPElevation == lastElevation) {
            noChangeCount++;
            if (noChangeCount >= MAX_NO_CHANGE) {
                Motor_Stop();
                LinearMotor.angleError = true;
                return;
            }
        } else {
            noChangeCount = 0; // judëjimas ávyko ? resetinam
        }

        // jei pasiekta ±1 laipsnio tikslumo ribos (ar ±0)
        if (SensorData.Elevation == angle) {
            Motor_Stop();
            targetReached = true; // tikslas pasiektas
            LinearMotor.angleError = false;
        }
    } else {
        // jei targetReached ir esame ±backlash intervale ? sustojam
        Motor_Stop();
        LinearMotor.angleError = false;
    }

    lastElevation = SensorData.HPElevation;
}




