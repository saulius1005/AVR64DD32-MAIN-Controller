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

	
    while (1) 
    {
		RS485Receiver(); //RS485 communication
		FOReceiver(); // Received Fiber optic data
		ReadJoystickValues(); //Joystick read
		work();
		screen_write_formatted_text("SE:%3d TE:%3d", 0, ALIGN_LEFT, SensorData.Elevation, Target.elevation);
		screen_write_formatted_text("SA:%3d TA:%3d", 1, ALIGN_LEFT, SensorData.Azimuth, Target.azimuth);
		screen_write_formatted_text("SCU:%4d SCI:%4d", 2, ALIGN_LEFT, SensorData.PVU, SensorData.PVI);
		screen_write_formatted_text("%03d|%03d", 4, ALIGN_CENTER, WSData.azimuth, WSData.elevation);
		screen_write_formatted_text("%03d|%d|%d|%d", 5, ALIGN_CENTER, WSData.topelevation, WSData.windspeed, WSData.winddirection, WSData.lightlevel);

		_delay_ms(100);
    }
}
