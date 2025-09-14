/*
 * Actions.c
 *
 * Created: 2025-09-13 19:52:13
 *  Author: Saulius
 */ 
#include "Settings.h"
#include "ActionsVar.h"

// Pagalbinë funkcija: normalizuoja kampà á [0,360)
int16_t normalize(int16_t angle) {
	angle %= 360;
	if (angle < 0) angle += 360;
	return angle;
}

// Pagalbinë: apskaièiuoja maþiausià kampiná atstumà
int16_t angle_diff(int16_t a, int16_t b) {
	int16_t d = abs(a - b) % 360;
	return (d > 180) ? 360 - d : d;
}

void get_safe_azimuth() {
	// Galimos saugios kryptys
	int16_t safe1 = normalize((WSData.winddirection * 45) + 90);
	int16_t safe2 = normalize((WSData.winddirection * 45) - 90);

	bool valid1 = (safe1 >= MIN_AZIMUTH && safe1 <= MAX_AZIMUTH);
	bool valid2 = (safe2 >= MIN_AZIMUTH && safe2 <= MAX_AZIMUTH);

	if (valid1 && valid2) {
		int16_t d1 = angle_diff(SensorData.Azimuth, safe1);
		int16_t d2 = angle_diff(SensorData.Azimuth, safe2);
		Target.azimuth = (d1 <= d2) ? safe1 : safe2;
		} else if (valid1) {
		Target.azimuth = safe1;
		} else {
		Target.azimuth = safe2; // visada bus bent vienas tinkamas
	}
}

void ReachTarget(){
	if (SensorData.Elevation == Target.elevation) {
		LinearMotor_stop();
		LinearMotor_disable();
	} 
	else if(SensorData.Elevation < (Target.elevation - ELEVATION_BACKLASH) || SensorData.Elevation > (Target.elevation + ELEVATION_BACKLASH)){
		LinearMotor_enable();
		LinearMotor_start();
		if (SensorData.Elevation < (Target.elevation - ELEVATION_BACKLASH)){
			LinearMotor_set_direction(1);
		}
		else if(SensorData.Elevation > (Target.elevation + ELEVATION_BACKLASH)){
			LinearMotor_set_direction(0);
		}
	}
	if (SensorData.Azimuth == Target.azimuth) {
		Stepper_stop();
		Stepper_disable();
	} 
	else  if(SensorData.Azimuth < (Target.azimuth - AZIMUTH_BACKLASH) || SensorData.Azimuth > (Target.azimuth + AZIMUTH_BACKLASH)){
		Stepper_enable();
		Stepper_start();
		if (SensorData.Azimuth < (Target.azimuth - AZIMUTH_BACKLASH)){
			Stepper_set_direction(1);
		}
		else if(SensorData.Azimuth > (Target.azimuth + AZIMUTH_BACKLASH)){
			Stepper_set_direction(0);
		}
	}
}

void work(){
	if(WSData.windspeed > MAX_WIND){
		get_safe_azimuth();
		Target.elevation = SAFE_ELEVATION;
	}
	else{
		if(WSData.lightlevel >= MIN_LIGHT_LEVEL){ // if minimum light level reached work as normal
			Target.azimuth = WSData.azimuth;
			Target.elevation = WSData.elevation;
		}
		else{ // if not go to best day position (early morning, late at evening, or just dark day)
			Target.azimuth = 180; //South
			Target.elevation = WSData.topelevation; //day top elevation
		}
			ReachTarget();
	}
}