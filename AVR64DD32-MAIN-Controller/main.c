/*
 * Created: 2025-04-30 16:52:56
 * Author: Saulius
 */

#include "Settings.h"

int main(void)
{
    CLOCK_XOSCHF_clock_init();
    GPIO_init();
	LinearMotor_init();
	Stepper_init();
    I2C_init();
    ADC0_init();
    USART0_init();
    USART1_init();
    screen_init();
    screen_clear();
	//TCB_init();
    while (1) 
    {
		RS485Receiver(); //RS485 communication
		FOReceiver(); // Received Fiber optic data
		ReadJoystickValues(); //Joystick read
		work();
		windows();

		//_delay_ms(100);
    }
}
