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
	bool JustBoot = false;
    while (1) 
    {		
		FOReceiver(); // Read Sensor data from TopController
		RS485Receiver(); //Read data and send answer to Weather station
		if(JustBoot)
			work();//Actions with motors
		windows();
		JustBoot = true;
    }
}
