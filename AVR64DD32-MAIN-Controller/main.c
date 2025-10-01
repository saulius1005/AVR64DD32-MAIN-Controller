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
	_delay_ms(300); //Let to boot Top controller
	FOReceiver(); // Received Fiber optic data
	RS485Receiver(); //RS485 communication
    while (1) 
    {
		RS485Receiver(); //RS485 communication
		FOReceiver(); // Received Fiber optic data
		work();//Actions with motors
		windows();
    }
}
