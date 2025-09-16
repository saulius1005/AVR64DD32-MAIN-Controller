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


	static uint16_t lastazimuth = 65535;
	static uint8_t stuckcount = 0;
	static uint8_t stuckcount2 = 0;
/*	if (SensorData.Elevation == Target.elevation) {
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
		}*/

if(SensorData.FO_no_power_fault == false){
	if (SensorData.Azimuth == Target.azimuth) {
		// Pasiektas tikslas
		Stepper_stop();
		Stepper_disable();
		SensorData.FO_lost_connecton_fault = false;
		stuckcount = 0;
	}
	else {
/*
		if (SensorData.Azimuth < (Target.azimuth - AZIMUTH_BACKLASH) ||
		SensorData.Azimuth > (Target.azimuth + AZIMUTH_BACKLASH)) {*/

			if (lastazimuth != SensorData.HPAzimuth) {
				SensorData.FO_lost_connecton_fault = false;
				stuckcount = 0;
				stuckcount2 = 0;
				Stepper_enable();			

				if (SensorData.Azimuth < (Target.azimuth - AZIMUTH_BACKLASH)) {
					Stepper_set_direction(1); // pirmyn
					Stepper_start();
					// Patikrinam krypties atitikimà
					if (SensorData.HPAzimuth <= lastazimuth) {
						// jutiklis nesikeièia teisinga kryptimi
						if(++stuckcount == 10){
							SensorData.FO_lost_connecton_fault = true;
							Stepper_stop();
							Stepper_disable();
						}
					}
				}
				else if (SensorData.Azimuth > (Target.azimuth + AZIMUTH_BACKLASH)) {
					Stepper_set_direction(0); // atgal
					Stepper_start();

					// Patikrinam krypties atitikimà
					if (SensorData.HPAzimuth >= lastazimuth) {
						// jutiklis nesikeièia teisinga kryptimi
						if(++stuckcount == 10){
						SensorData.FO_lost_connecton_fault = true;
						Stepper_stop();
						Stepper_disable();
						}
					}
				}
			}
			else {
				// Jutiklis nerodo pokyèio ? laikom, kad uþstrigo
				if(++stuckcount2 == 10){
				SensorData.FO_lost_connecton_fault = true;
				Stepper_stop();
				Stepper_disable();
				}
			}

			// Atnaujinam paskutinæ reikðmæ
			lastazimuth = SensorData.HPAzimuth;
		//}
	}
}
else{
	Stepper_stop();
	Stepper_disable();
}

}


#define SENSOR_DEADBAND      0.2f   // maþiausias pokytis, kurá laikome tikru judesiu
#define STUCK_LIMIT          3      // ciklø skaièius prieð fault

static float lastAzimuth = 0.0f;
static uint8_t stuckCount = 0;
static uint8_t noChangeCount = 0;

void StepperControl()
{
	if(SensorData.FO_no_power_fault) return; // jei nëra maitinimo, neveikia

	float delta = SensorData.HPAzimuth - lastAzimuth;

	// Triukðmo zona: smulkûs ðokinëjimai ignoruojami
	if(fabs(delta) < SENSOR_DEADBAND) delta = 0.0f;

	// Tikslinë pozicija pasiekta
	if(fabs(SensorData.Azimuth - Target.azimuth) <= AZIMUTH_BACKLASH)
	{
		Stepper_stop();
		Stepper_disable();
		SensorData.FO_lost_connecton_fault = false;
		stuckCount = 0;
		noChangeCount = 0;
		lastAzimuth = SensorData.HPAzimuth;
		return;
	}

	// Ájungiam stepperá
	Stepper_enable();
	Stepper_start();

	// Nustatom kryptá pagal Target
	if(SensorData.Azimuth < Target.azimuth - AZIMUTH_BACKLASH)
	{
		Stepper_set_direction(1); // pirmyn

		// Jeigu jutiklis rodo prieðinga kryptá
		if(delta < -SENSOR_DEADBAND)
		{
			if(++stuckCount >= STUCK_LIMIT)
			{
				SensorData.FO_lost_connecton_fault = true;
				Stepper_stop();
				Stepper_disable();
			}
		}
		else if(delta > SENSOR_DEADBAND)
		{
			stuckCount = 0; // teisinga kryptis, resetinam skaitliukà
		}
	}
	else if(SensorData.Azimuth > Target.azimuth + AZIMUTH_BACKLASH)
	{
		Stepper_set_direction(0); // atgal

		// Jeigu jutiklis rodo prieðinga kryptá
		if(delta > SENSOR_DEADBAND)
		{
			if(++stuckCount >= STUCK_LIMIT)
			{
				SensorData.FO_lost_connecton_fault = true;
				Stepper_stop();
				Stepper_disable();
			}
		}
		else if(delta < -SENSOR_DEADBAND)
		{
			stuckCount = 0; // teisinga kryptis
		}
	}

	// Patikrinam ar jutiklis „uþstrigo“ (delta = 0)
	if(delta == 0.0f)
	{
		if(++noChangeCount >= STUCK_LIMIT)
		{
			SensorData.FO_lost_connecton_fault = true;
			Stepper_stop();
			Stepper_disable();
		}
	}
	else
	{
		noChangeCount = 0; // judëjimas ávyko
	}

	// Atnaujinam paskutinæ reikðmæ
	lastAzimuth = SensorData.HPAzimuth;
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
				//ReachTarget();
				StepperControl();
	}


}