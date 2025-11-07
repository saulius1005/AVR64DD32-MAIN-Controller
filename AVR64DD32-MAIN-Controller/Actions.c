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

void AutoMotorControl(MotorType motor)
{
	MotorControlObj* m = motor ? &StepperMotorCtrl : &LinearMotorCtrl;

	uint8_t stuck_limit = STUCK_LIMIT;
	int16_t deadband = SENSOR_DEADBAND;
	uint8_t start_delay_limit = START_DEALY;

	int32_t pos = *m->sensor.position;
	int32_t target = *m->sensor.target;
	int32_t filtered = *m->sensor.positionFiltered;
	int32_t last = *m->sensor.lastPosition;
	int32_t delta = filtered - last;

	// 2. Kryptis
	bool dir = (pos < target);
	m->iface.set_direction(dir);
	// Jeigu pasikeitë kryptis, duodam laiko reduktoriams
	if (dir != m->lastDir) {
		m->startDelay = 0;   // resetuojam „atleidimo“ laikmatá
		m->lastDir = dir;
	}

	// 3. End switch logika
	bool atMin = *m->sensor.endswitchMin;
	bool atMax = *m->sensor.endswitchMax;
	if ((dir && atMax) || (!dir && atMin)) {
		m->iface.stop();
		m->iface.disable();
		*m->sensor.targetReached = true;
		return;
	}

	// 4. Tikslas pasiektas
	if (pos == target) {
		m->iface.stop();
		m->iface.disable();
		*m->sensor.faultFlag = 0; //no fault
		*m->sensor.targetReached = true;
		m->stuckCount = 0;
		m->noChangeCount = 0;
		m->startDelay = 0;   // resetuojam „atleidimo“ laikmatá
		return;
	}

	// 5. Backlash logika
	if ((pos < target - m->backlash || pos > target + m->backlash) || !*m->sensor.targetReached) {
		m->iface.enable();
		m->iface.start();
		*m->sensor.targetReached = false;
	}

	// 6. Delta filtras
	if (delta > -deadband && delta < deadband) delta = 0;

	// 7. Uþstrigimo tikrinimas
	if (pos < target - m->backlash) {
		if (delta < -deadband) {
			if (++m->stuckCount >= stuck_limit) {
				*m->sensor.faultFlag = 1; //stuck at moving forward
				m->iface.stop();
				m->iface.disable();
			}
			} else if (delta > deadband) {
			m->stuckCount = 0;
		}
	}
	else if (pos > target + m->backlash) {
		if (delta > deadband) {
			if (++m->stuckCount >= stuck_limit) {
				*m->sensor.faultFlag = 2; //stuck at moving backward
				m->iface.stop();
				m->iface.disable();
			}
			} else if (delta < -deadband) {
			m->stuckCount = 0;
		}
	}

	// 8. Uþstrigimo tikrinimas su "start delay"
	if (m->startDelay < start_delay_limit) {
		m->startDelay++;
		} else {		
		if (delta == 0 && !*m->sensor.targetReached) {// èia eina áprasta uþstrigimo logika:
			if (++m->noChangeCount >= stuck_limit) {
				*m->sensor.faultFlag = 3;
				m->iface.stop();
				m->iface.disable();
			}
			} else {
			m->noChangeCount = 0;
		}
	}
	*m->sensor.lastPosition = filtered;
}

void ManualMotorControl(MotorType motor){
	MotorControlObj* m = motor ? &StepperMotorCtrl : &LinearMotorCtrl; //choose motor control stepper or linear

	int16_t *joy_axis = (motor == MOTOR_STEPPER) ? &Joystick.X_Axis : &Joystick.Y_Axis; //choose joystick axis (for stepper - X axis, for linear Y axis)
	bool SwapStepDir = (motor == MOTOR_STEPPER) ? true : false; //swaping directions for stepper, and keep as usual for linear

	// Jei joystick'as centre — sustabdyti
	if (*joy_axis == 0) {
		m->iface.stop();
		m->iface.disable();
		return;
	}

	bool forward = (*joy_axis > 0);
	bool at_limit = forward ? *m->sensor.endswitchMax : *m->sensor.endswitchMin;

	// Jei pasiektas kraðtinis jungiklis — sustabdyti
	if (at_limit) {
		m->iface.stop();
		m->iface.disable();
		return;
	}

	// Kitu atveju — judëti atitinkama kryptimi
	m->iface.enable();
	m->iface.set_direction(forward ? SwapStepDir : !SwapStepDir);
	m->iface.start();
}

void Emergency_STOP(MotorType motor){
	MotorControlObj* m = motor ? &StepperMotorCtrl : &LinearMotorCtrl; //choose motor control stepper or linear
	m->iface.stop();
	m->iface.disable();
	*m->sensor.faultFlag = 4; //emergency stop
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
		if((!WSData.WS_lost_connecton_fault) && (!SensorData.FO_lost_connecton_fault) && (!SensorData.FO_bad_signal_fault)){ // only receiving data from RS485 network (Weather Station) and from top controller
			if(WSData.windspeed > MAX_WIND){
				get_safe_azimuth();
			Target.elevation = SAFE_ELEVATION;
			}
			else{// normal work
				if(WSData.lightlevel >= MIN_LIGHT_LEVEL){ // if minimum light level reached work as normal
					if(WSData.azimuth > MAX_AZIMUTH)
						Target.azimuth = MAX_AZIMUTH;
					else if( WSData.azimuth < MIN_AZIMUTH)
						Target.azimuth = MIN_AZIMUTH;
					else
						Target.azimuth = WSData.azimuth;
					if(WSData.elevation > MAX_ELEVATION)
						Target.elevation = MAX_ELEVATION;
					else if(WSData.elevation < MIN_ELEVATION)
						Target.elevation = MIN_ELEVATION;
					else
						Target.elevation = WSData.elevation;
				}
				else{ // if not go to best day position (early morning, late at evening, or just dark day)
					Target.azimuth = 171; //South -9 degree
					Target.elevation = WSData.topelevation; //day top elevation
				}		 
				AutoMotorControl(MOTOR_LINEAR);
				AutoMotorControl(MOTOR_STEPPER);
			}
		}	
		else{// when connection was lost in action
			Emergency_STOP(MOTOR_STEPPER);
			Emergency_STOP(MOTOR_LINEAR);
		}	
	}
}