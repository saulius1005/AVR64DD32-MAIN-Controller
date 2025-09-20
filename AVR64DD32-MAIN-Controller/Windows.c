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
			values[0] = WSData.elevation;
			values[1] = SensorData.Elevation;
			values[2] = WSData.azimuth;
			values[3] = SensorData.Azimuth;
			for (uint8_t i=0; i<4; i++){
				if(show.lastValues[i] != values[i]){
/*
				screen_write_formatted_text("Update", 0, ALIGN_CENTER); //for screen updating debug
				_delay_ms(100);
				screen_write_formatted_text("      ", 0, ALIGN_CENTER);*/
				update = true;
				break;
				}
			}
			for (uint8_t i=0; i<4; i++){
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
	switch (show.window){
		case 0:
			if(screenUpdater(0)){
				screen_write_formatted_text("Elevation:", 2, ALIGN_LEFT);
				screen_write_formatted_text("%3d/ %3d", 2, ALIGN_RIGHT, WSData.elevation, SensorData.Elevation);
				screen_write_formatted_text("Azimuth:", 3, ALIGN_LEFT);
				screen_write_formatted_text("%3d/ %3d", 3, ALIGN_RIGHT, WSData.azimuth, SensorData.Azimuth);
			}
		break;
		case 1:
			if(screenUpdater(1)){
				//Solar panels electrical information
				screen_write_formatted_text("S.P. Voltage", 0, ALIGN_LEFT);
				screen_write_formatted_text("%3d.%01d", 0, ALIGN_RIGHT, SensorData.PVU/10, SensorData.PVU%10);
				screen_write_formatted_text("S.P Current:", 1, ALIGN_LEFT);
				screen_write_formatted_text("%3d.%02d", 1, ALIGN_RIGHT, SensorData.PVI/100, abs(SensorData.PVI%100));
				screen_write_formatted_text("---------------------", 2, ALIGN_LEFT);
				//Azimuth (Stepper) motor electrical information
				screen_write_formatted_text("St.M. Voltage", 3, ALIGN_LEFT);
				screen_write_formatted_text("%3d.%01d", 3, ALIGN_RIGHT, StepperMotor.measuredVoltage/10, StepperMotor.measuredVoltage%10);
				screen_write_formatted_text("St.M. Current:", 4, ALIGN_LEFT);
				screen_write_formatted_text("%3d.%02d", 4, ALIGN_RIGHT, StepperMotor.measuredCurrent/100, abs(StepperMotor.measuredCurrent%100));
				screen_write_formatted_text("---------------------", 5, ALIGN_LEFT);
				//Elevation (Linear) motor electical information
				screen_write_formatted_text("L.M. Voltage", 6, ALIGN_LEFT);
				screen_write_formatted_text("%3d.%01d", 6, ALIGN_RIGHT, LinearMotor.measuredVoltage/10, LinearMotor.measuredVoltage%10);
				screen_write_formatted_text("L.M. Current:", 7, ALIGN_LEFT);
				screen_write_formatted_text("%3d.%02d", 7, ALIGN_RIGHT, LinearMotor.measuredCurrent/100, abs(LinearMotor.measuredCurrent%100));
			}
		break;
	}
	

}