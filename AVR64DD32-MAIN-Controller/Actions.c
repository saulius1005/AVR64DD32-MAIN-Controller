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

/*
void StepperControl()
{
	if(SensorData.FO_lost_signal_fault) return; // jei nëra maitinimo, neveikia

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
}*/

void LinearMotorControl(void)
{
	// 1. Tikrinam FO jungtá
	if (SensorData.FO_lost_connecton_fault) {
		LinearMotor_stop();
		LinearMotor_disable();
		return;
	}

	// 2. Tikslas pasiektas
	if (SensorData.Elevation == Target.elevation) {
		LinearMotor_stop();
		LinearMotor_disable();
		SensorData.FO_elevation_sensor_fault = false;
		Target.elevation_reached = true;
		LinearMotor.stuckCount = 0;
		LinearMotor.noChangeCount = 0;
		return;
	}

	// 3. Judëjimo paleidimas / palaikymas
	bool inBacklash = (SensorData.Elevation >= (Target.elevation - ELEVATION_BACKLASH)) &&
	(SensorData.Elevation <= (Target.elevation + ELEVATION_BACKLASH));

	if (!inBacklash || !Target.elevation_reached) {
		LinearMotor_start();
		LinearMotor_enable();
		Target.elevation_reached = false;
	}

	// 4. Apskaièiuojam pokytá
	int32_t delta = (int32_t)SensorData.HPElevation - (int32_t)Target.lastElevation;
	if (delta > -SENSOR_DEADBAND && delta < SENSOR_DEADBAND) {
		delta = 0; // triukðmo zona
	}

	// 5. Nustatome kryptá
	if (SensorData.Elevation < Target.elevation) {
		LinearMotor_set_direction(1);
		} else if (SensorData.Elevation > Target.elevation) {
		LinearMotor_set_direction(0);
	}

	// 6. Uþstrigimo tikrinimas (neteisinga kryptis)
	if (SensorData.Elevation < (Target.elevation - ELEVATION_BACKLASH)) {
		if (delta < -SENSOR_DEADBAND && ++LinearMotor.stuckCount >= STUCK_LIMIT) {
			SensorData.FO_elevation_sensor_fault = true;
			LinearMotor_stop();
			LinearMotor_disable();
			} else if (delta > SENSOR_DEADBAND) {
			LinearMotor.stuckCount = 0;
		}
		} else if (SensorData.Elevation > (Target.elevation + ELEVATION_BACKLASH)) {
		if (delta > SENSOR_DEADBAND && ++LinearMotor.stuckCount >= STUCK_LIMIT) {
			SensorData.FO_elevation_sensor_fault = true;
			LinearMotor_stop();
			LinearMotor_disable();
			} else if (delta < -SENSOR_DEADBAND) {
			LinearMotor.stuckCount = 0;
		}
	}

	// 7. Tikrinam ar „uþstrigo“ vietoje (nëra jokio judesio)
	if (delta == 0 && !Target.elevation_reached) {
		if (++LinearMotor.noChangeCount >= STUCK_LIMIT) {
			SensorData.FO_elevation_sensor_fault = true;
			LinearMotor_stop();
			LinearMotor_disable();
		}
		} else {
		LinearMotor.noChangeCount = 0;
	}

	// 8. Iðsaugom paskutinæ reikðmæ
	Target.lastElevation = SensorData.HPElevation;
}

void MotorControl(MotorControlObj* m)
{
	// 1. FO jungtis
	if (SensorData.FO_lost_connecton_fault) {
		m->iface.stop();
		m->iface.disable();
		return;
	}

	// 2. Tikslas pasiektas
	if (*m->sensor.position == *m->sensor.target) {
		m->iface.stop();
		m->iface.disable();
		*m->sensor.faultFlag = false;
		*m->sensor.targetReached = true;
		m->stuckCount = 0;
		m->noChangeCount = 0;
		return;
	}

	// 3. Backlash logika
	bool inBacklash = (*m->sensor.position >= (*m->sensor.target - m->backlash)) &&
	(*m->sensor.position <= (*m->sensor.target + m->backlash));

	if (!inBacklash || !*m->sensor.targetReached) {
		m->iface.start();
		m->iface.enable();
		*m->sensor.targetReached = false;
	}

	// 4. Pokytis
	int32_t delta = (int32_t)(*m->sensor.positionFiltered) - (int32_t)(*m->sensor.lastPosition);
	if (delta > -SENSOR_DEADBAND && delta < SENSOR_DEADBAND) {
		delta = 0;
	}

	// 5. Kryptis
	if (*m->sensor.position < *m->sensor.target) {
		m->iface.set_direction(1);
		} else if (*m->sensor.position > *m->sensor.target) {
		m->iface.set_direction(0);
	}

	// 6. Uþstrigimo tikrinimas (neteisinga kryptis)
	if (*m->sensor.position < (*m->sensor.target - m->backlash)) {
		if (delta < -SENSOR_DEADBAND && ++m->stuckCount >= STUCK_LIMIT) {
			*m->sensor.faultFlag = true;
			m->iface.stop();
			m->iface.disable();
			} else if (delta > SENSOR_DEADBAND) {
			m->stuckCount = 0;
		}
		} else if (*m->sensor.position > (*m->sensor.target + m->backlash)) {
		if (delta > SENSOR_DEADBAND && ++m->stuckCount >= STUCK_LIMIT) {
			*m->sensor.faultFlag = true;
			m->iface.stop();
			m->iface.disable();
			} else if (delta < -SENSOR_DEADBAND) {
			m->stuckCount = 0;
		}
	}

	// 7. Uþstrigimas vietoje
	if (delta == 0 && !*m->sensor.targetReached) {
		if (++m->noChangeCount >= STUCK_LIMIT) {
			*m->sensor.faultFlag = true;
			m->iface.stop();
			m->iface.disable();
		}
		} else {
		m->noChangeCount = 0;
	}

	// 8. Atnaujinam paskutinæ reikðmæ
	*m->sensor.lastPosition = *m->sensor.positionFiltered;
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
				//StepperControl();
				//LinearMotorControl();
				MotorControl(&LinearMotorCtrl);
				//MotorControl(&StepperMotorCtrl);
	}


}