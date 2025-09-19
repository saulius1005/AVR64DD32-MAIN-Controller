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

bool screenUpdater(uint8_t window){
	uint16_t values[MAX_VARS]={0};
	bool update = false;
	if(show.lastWindow != show.window)
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
	}
	return update;
}


void windows() {
	switch (show.window){
		case 0:
			if(screenUpdater(0)){
				screen_write_formatted_text("El:", 2, ALIGN_LEFT);
				screen_write_formatted_text("%3d/ %3d", 2, ALIGN_RIGHT, WSData.elevation, SensorData.Elevation);
				screen_write_formatted_text("Az:", 3, ALIGN_LEFT);
				screen_write_formatted_text("%3d/ %3d", 3, ALIGN_RIGHT, WSData.azimuth, SensorData.Azimuth);
			}

		break;
	}
	show.lastWindow = show.window;

}