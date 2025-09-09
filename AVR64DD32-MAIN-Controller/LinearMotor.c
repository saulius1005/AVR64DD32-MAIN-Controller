/*
 * LinearMotor.c
 *
 * Created: 2025-09-09 14:20:10
 *  Author: Saulius
 */ 
#include "Settings.h"
#include "LinearMotorVar.h"

void Motor_SetDirection(void)
{
    if (LinearMotor.newDirection != LinearMotor.lastDirection)  // tik jei kryptis pasikeitë
    {
        // 1. Stop PWM
        TCA0.SPLIT.CTRLA &= ~TCA_SPLIT_ENABLE_bm;
		TCA0.SPLIT.CTRLESET = TCA_SPLIT_CMD_RESET_gc; 
        PORTD.OUTCLR = PIN3_bm;  // PWM out low (jei reikia)
        // 2. Disable driver
		_delay_ms(500);
        PORTD.OUTSET = PIN2_bm;  // DIS=1
        _delay_ms(100);            // uþtenka 1–5 ms, 100ms yra labai daug

        // 3. Nustatom kryptá
        if (LinearMotor.newDirection) {
            PORTD.OUTSET = PIN5_bm;   // UP
        } else {
            PORTD.OUTCLR = PIN5_bm;   // DOWN
        }

        // 4. Atnaujinam atmintá
        LinearMotor.lastDirection = LinearMotor.newDirection;
        // 5. Enable driver
        PORTD.OUTCLR = PIN2_bm;  // DIS=0
		_delay_ms(500); 

        // 6. Start PWM
     /*   TCA0.SPLIT.CTRLA |= TCA_SPLIT_ENABLE_bm;
		_delay_ms(100);*/
		TCA0_init_WO3_PWM(10000, 50);
    }
}