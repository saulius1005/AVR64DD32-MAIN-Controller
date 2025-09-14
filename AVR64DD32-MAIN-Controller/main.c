/*
 * Created: 2025-04-30 16:52:56
 * Author: Saulius
 */

#include "Settings.h"

int main(void)
{
    CLOCK_XOSCHF_clock_init();
    GPIO_init();
    I2C_init();
    ADC0_init();
    USART0_init();
    USART1_init();
    screen_init();
    screen_clear();
	LinearMotor_init();
	Stepper_init();
	
    while (1) 
    {
		RS485Receiver(); //RS485 communication
		FOReceiver(); // Received Fiber optic data
		ReadJoystickValues(); //Joystick read
		work();
		screen_write_formatted_text("SE:%3d TE:%3d", 0, ALIGN_LEFT, SensorData.Elevation, Target.elevation);
		screen_write_formatted_text("SA:%3d TA:%3d", 1, ALIGN_LEFT, SensorData.Azimuth, Target.azimuth);
		screen_write_formatted_text("SCU:%3d SCI:%3d", 2, ALIGN_LEFT, SensorData.PVU, SensorData.PVI);

		_delay_ms(100);

/*
		//RS485 data raw data, not filtered or maintained (azimuth, elevation angles, day top elevation, wind speed and direction, light level in mV)
		screen_write_formatted_text("%d|%d|%d|%d|%d|%d", 0, ALIGN_CENTER, WSData.azimuth, WSData.elevation, WSData.topelevation, WSData.windspeed, WSData.winddirection, WSData.lightlevel);
		//Fiber optic data
		screen_write_formatted_text("PVU:%4d PVI:4%d", 1, ALIGN_LEFT, SensorData.PVU, SensorData.PVI);
		screen_write_formatted_text("E:%d|%d  A:%d|%d", 2, ALIGN_LEFT, SensorData.ElMin, SensorData.ElMax, SensorData.AzMin, SensorData.AzMax); //End switch values Elevation min max, azimuth min max
		//Fiber optic angle sensors + both motors drivers status data
		screen_write_formatted_text("el.:%3d EF: %d", 3, ALIGN_LEFT, SensorData.Elevation, Read_LinearMotor_EF());
		screen_write_formatted_text("az:%3d PEND:%d ALM:%d", 4, ALIGN_LEFT, SensorData.Azimuth, Read_Stepper_PEND(), Read_Stepper_ALM());
		//Voltage and current sensors on board data
		screen_write_formatted_text("LM U:%4d I:%4d", 5, ALIGN_LEFT, Read_LinearMotor_Voltage(), Read_LinearMotor_Current());
		screen_write_formatted_text("SM U:%4d I:%4d", 6, ALIGN_LEFT, Read_Stepper_Voltage(), Read_Stepper_Current());
		//Joistic data
		screen_write_formatted_text("X:%2d Y:%2d B:%d", 7, ALIGN_LEFT, Joystick.X_Axis, Joystick.Y_Axis, Joystick.Button);
		_delay_ms(100);

		if (SensorData.Azimuth == 0) { //basic stepper and linear motors test
			Stepper_stop();	
			Stepper_disable();
			} else {
			Stepper_enable();
			Stepper_start();
			if (SensorData.Azimuth <= 180){
				Stepper_set_direction(1);
			} 
			else{
				Stepper_set_direction(0);
			}
		}
		if (SensorData.Elevation == 0) {
			LinearMotor_stop();
			LinearMotor_disable();
			} else {
			LinearMotor_enable();
			LinearMotor_start();
			if (SensorData.Elevation <= 180){
				LinearMotor_set_direction(1);
			}
			else{
				LinearMotor_set_direction(0);
			}
		}*/
    }
}
