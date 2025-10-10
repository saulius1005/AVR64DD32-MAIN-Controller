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

//Motor control function wrtited based on void LinearMotorControl()
void AutoMotorControl(MotorType motor)
{
	MotorControlObj* m = motor ? &StepperMotorCtrl : &LinearMotorCtrl;
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
		m->iface.enable();
		m->iface.start();
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

void ManualMotorControl(MotorType motor){
	MotorControlObj* m = motor ? &StepperMotorCtrl : &LinearMotorCtrl; //choose motor control stepper or linear

	int16_t *joy_axis = (motor == MOTOR_STEPPER) ? &Joystick.X_Axis : &Joystick.Y_Axis; //choose joystick axis (for stepper - X axis, for linear Y axis)
	bool SwapStepDir = (motor == MOTOR_STEPPER) ? true : false; //swaping directions for stepper, and keep as usual for linear

	if(*joy_axis == 0){ 
		m->iface.stop();
		m->iface.disable();		
	}
	else{
		m->iface.enable(); //enabling driver
		if(*joy_axis > 0)
			m->iface.set_direction(SwapStepDir); //set direction (stepper 1, linear 0)
		else
			m->iface.set_direction(!SwapStepDir); // (stepper 0, linear 1)
		m->iface.start(); // start generating pulses
	}
}

void ReadMotorData(MotorType motor){
	MotorControlObj* m = motor ? &StepperMotorCtrl : &LinearMotorCtrl; //choose motor control stepper or linear
	*m->voltage = m->iface.read_voltage(); //read and save voltage
	*m->current = m->iface.read_current(); //read and save current
}

void work(){
	ReadMotorData(MOTOR_STEPPER); //Read stepper motor voltage and current
	ReadMotorData(MOTOR_LINEAR); //REad linear motor voltage and current
	if(Joystick.LatchSwitch){ //Manual mode: basic as possible- ignores all errors. Just pure motor control
		ManualMotorControl(MOTOR_STEPPER);
		ManualMotorControl(MOTOR_LINEAR);
	}
	else{//Auto mode
		if(!WSData.WS_lost_connecton_fault){ // only receiving data from RS485 network (Weather Station)
			if(WSData.windspeed > MAX_WIND){
				get_safe_azimuth();
			Target.elevation = SAFE_ELEVATION;
			}
			else{// normal work
				if(WSData.lightlevel >= MIN_LIGHT_LEVEL){ // if minimum light level reached work as normal
					Target.azimuth = WSData.azimuth;
					Target.elevation = WSData.elevation;
				}
				else{ // if not go to best day position (early morning, late at evening, or just dark day)
					Target.azimuth = 180; //South
					Target.elevation = WSData.topelevation; //day top elevation
				}		 
				Target.azimuth = WSData.azimuth;
				Target.elevation = WSData.elevation;
				AutoMotorControl(MOTOR_LINEAR);
				AutoMotorControl(MOTOR_STEPPER);
			}
		}		
	}
}