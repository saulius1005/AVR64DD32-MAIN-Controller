/*
 * Windows.c
 *
 * Created: 2024-12-11 21:50:34
 * Author: Saulius
 *
 * This file provides functions for displaying and managing time, date, location (latitude, longitude),
 * altitude, and timezone on the screen. It includes extraction and formatting of specific data for display.
 */

#include "Settings.h"
#include "windowsVar.h"

bool screenUpdater(uint8_t window){ //update window data if any changes only
	uint16_t values[MAX_VARS]={0};
	bool update = false;

	if(show.lastWindow != window)
		screen_clear();
	switch (window){
		case 0:
			values[0] = Target.elevation;
			values[1] = SensorData.Elevation;
			values[2] = Target.azimuth;
			values[3] = SensorData.Azimuth;
			values[4] = Joystick.LatchSwitch;
			values[5] = SensorData.FO_data_fault;
			values[6] = SensorData.FO_bad_signal_fault;
			values[7] = SensorData.FO_lost_connecton_fault;
			values[8] = SensorData.FO_elevation_sensor_fault;
			values[9] = SensorData.FO_azimuth_sensor_fault;
			values[10] = WSData.WS_lost_connecton_fault;
			values[11] = WSData.WS_data_fault;
			for (uint8_t i=0; i<11; i++){
				if(show.lastValues[i] != values[i]){
				update = true;
				break;
				}
			}
			for (uint8_t i=0; i<11; i++){
				show.lastValues[i] = values[i];
			}
		break;
		case 1:
			values[0] = SensorData.PVU;
			values[1] = SensorData.PVI;
			values[2] = StepperMotor.measuredVoltage;
			values[3] = StepperMotor.measuredCurrent;
			values[4] = LinearMotor.measuredVoltage;
			values[5] = LinearMotor.measuredCurrent;
			for (uint8_t i=0; i<6; i++){
				if(show.lastValues[i] != values[i]){
				update = true;
				break;
				}
			}
			for (uint8_t i=0; i<6; i++){
				show.lastValues[i] = values[i];
			}
		break;
	}
	show.lastWindow = window;
	return update;
}

void windows() {

	ReadJoystickValues(); //Joystick read

	if(!Joystick.LatchSwitch){//windows changing works if control is set as Auto.
		SelectWindow();
	}
	LatchSwitcher();
	switch (show.window){
		case 0:
			if(screenUpdater(0)){
				screen_write_formatted_text("%s", 0, ALIGN_CENTER, Joystick.LatchSwitch ? "Manual mode": " Auto mode ");			
				screen_write_formatted_text("---------------------", 1, ALIGN_CENTER);
				//1. Lost connection error- No data from Weather station (broken line, corosion, hardware fail and so on)
				//2. Bad CRC
				screen_write_formatted_text("W.S: %s %s", 2, ALIGN_LEFT,  WSData.WS_lost_connecton_fault ? "LCE": "   ", WSData.WS_data_fault ? "CRC": "   ");
				//1. USATR1 not receiving messages FO_lost_signal_fault meaning FO optic cut or Top controller fault, or onboard Attiny212 fault
				//1a. FO_lost_signal_fault 3 times in row leads to lost connection fault FO_lost_connecton_fault
				//2. Weak signal from FO coses FO_bad_signal_fault (receiving 000.. with good crc). Onboard Attiny212 works good
				//3. Bad CRC returns FO_data_fault											
				screen_write_formatted_text("T.C: %s %s %s", 3, ALIGN_LEFT, SensorData.FO_lost_connecton_fault ? "LCE": "   ", SensorData.FO_bad_signal_fault ? "FOE": "   ", SensorData.FO_data_fault ? "CRC": "   "  );
				screen_write_formatted_text("---------------------", 4, ALIGN_CENTER);
				screen_write_formatted_text("Elevation:", 5, ALIGN_LEFT);
				//1. Elevation sensordata and fault FO_elevation_sensor_fault error
				screen_write_formatted_text("%3d/ %3d%s", 5, ALIGN_RIGHT, Target.elevation, SensorData.Elevation, SensorData.FO_elevation_sensor_fault ? "!E": "  ");
				screen_write_formatted_text("Azimuth:", 6, ALIGN_LEFT);
				//1. Azimuth sensor data and fault FO_azimuth_sensor_fault
				screen_write_formatted_text("%3d/ %3d%s", 6, ALIGN_RIGHT, Target.azimuth, SensorData.Azimuth, SensorData.FO_azimuth_sensor_fault ? "!E": "  ");
			}
		break;
		case 1:
			if(screenUpdater(1)){
				//Solar panels electrical information
				screen_write_formatted_text("S.P. Voltage", 0, ALIGN_LEFT);
				screen_write_formatted_text("%3d.%01d", 0, ALIGN_RIGHT, SensorData.PVU/10, SensorData.PVU%10);
				screen_write_formatted_text("S.P Current:", 1, ALIGN_LEFT);
				screen_write_formatted_text("%3d.%02d", 1, ALIGN_RIGHT, SensorData.PVI/100, abs(SensorData.PVI%100));
				screen_write_formatted_text("---------------------", 2, ALIGN_CENTER);
				//Azimuth (Stepper) motor electrical information
				screen_write_formatted_text("St.M. Voltage", 3, ALIGN_LEFT);
				screen_write_formatted_text("%3d.%01d", 3, ALIGN_RIGHT, StepperMotor.measuredVoltage/10, StepperMotor.measuredVoltage%10);
				screen_write_formatted_text("St.M. Current:", 4, ALIGN_LEFT);
				screen_write_formatted_text("%3d.%02d", 4, ALIGN_RIGHT, StepperMotor.measuredCurrent/100, abs(StepperMotor.measuredCurrent%100));
				screen_write_formatted_text("---------------------", 5, ALIGN_CENTER);
				//Elevation (Linear) motor electical information
				screen_write_formatted_text("L.M. Voltage", 6, ALIGN_LEFT);
				screen_write_formatted_text("%3d.%01d", 6, ALIGN_RIGHT, LinearMotor.measuredVoltage/10, LinearMotor.measuredVoltage%10);
				screen_write_formatted_text("L.M. Current:", 7, ALIGN_LEFT);
				screen_write_formatted_text("%3d.%02d", 7, ALIGN_RIGHT, LinearMotor.measuredCurrent/100, abs(LinearMotor.measuredCurrent%100));
			}
		break;
	}
	

}