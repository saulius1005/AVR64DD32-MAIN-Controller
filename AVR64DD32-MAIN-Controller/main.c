/*
 * Created: 2025-04-30 16:52:56
 * Author: Saulius
 */

#include "Settings.h"

int main(void)
{
    // Initialize system clock, GPIO, I2C, ADC, USART, and screen
    CLOCK_XOSCHF_clock_init();
    GPIO_init();
    I2C_init();
    ADC0_init();
    USART0_init();
    USART1_init();
    screen_init();
    screen_clear(); // Clear the screen

	//screen_write_formatted_text("Screen test:", 0, ALIGN_LEFT); //simple  screen test
	TCA0_init_WO3_PWM(20000, 50);


    while (1) 
    {
		/*RS485_Led(RX_LED_ON); //RS485 RX TX LED test
		_delay_ms(100);
		RS485_Led(TX_LED_ON);
		_delay_ms(100);
		RS485_Led(RX_LED_OFF);
		_delay_ms(100);
		RS485_Led(TX_LED_OFF);
		_delay_ms(100);*/

		FOReceiver(); // Received Fiber optic test
		screen_write_formatted_text("%3d", 0, ALIGN_CENTER, SensorData.Elevation/100);
		screen_write_formatted_text("%3d", 1, ALIGN_CENTER, SensorData.Azimuth/100);
		screen_write_formatted_text("%3d", 2, ALIGN_LEFT, SensorData.PVU/10);
		screen_write_formatted_text("%3d", 2, ALIGN_RIGHT, SensorData.PVI/10);
		screen_write_formatted_text("%d", 3, ALIGN_LEFT, SensorData.ElMin);
		screen_write_formatted_text("%d", 3, ALIGN_RIGHT, SensorData.ElMax);
		screen_write_formatted_text("%d", 4, ALIGN_LEFT, SensorData.AzMin);
		screen_write_formatted_text("%d", 4, ALIGN_RIGHT, SensorData.AzMax);

		/*ReadJoystickValues(); //Joystick test
		screen_write_formatted_text("%3d", 0, ALIGN_CENTER, Joystick.X_Axis);
		screen_write_formatted_text("%3d", 1, ALIGN_CENTER, Joystick.Y_Axis);
		screen_write_formatted_text("%d", 2, ALIGN_CENTER, Joystick.Button);*/

		/*RS485Receiver(); //RS485 communication test
		screen_write_formatted_text("%d %d %d %d %d %d", 0, ALIGN_CENTER, WSData.azimuth, WSData.elevation, WSData.topelevation, WSData.windspeed, WSData.winddirection, WSData.lightlevel);*/


		if (SensorData.Elevation/100 > 180) {
			LinearMotor.newDirection = true;		
			} else {
			LinearMotor.newDirection = false;	
		}

		Motor_SetDirection();
    }
}
