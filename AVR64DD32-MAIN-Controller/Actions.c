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
/*
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
}*/

/*
void AutoMotorControl(MotorType motor) //v3
{
	MotorControlObj* m = motor ? &StepperMotorCtrl : &LinearMotorCtrl;

	uint8_t stuck_limit = STUCK_LIMIT;
	int16_t deadband = SENSOR_DEADBAND;

	int32_t pos = *m->sensor.position;
	int32_t target = *m->sensor.target;
	int32_t filtered = *m->sensor.positionFiltered;
	int32_t last = *m->sensor.lastPosition;
	int32_t delta = filtered - last;

	// 1. FO jungties klaida
	if (SensorData.FO_lost_connecton_fault) {
		m->iface.stop();
		m->iface.disable();
		return;
	}

	// 2. Kryptis
	bool dir = (pos < target);
	m->iface.set_direction(dir);

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
	if (abs(pos - target) <= deadband) {
		m->iface.stop();
		m->iface.disable();
		*m->sensor.faultFlag = false;
		*m->sensor.targetReached = true;
		m->stuckCount = 0;
		m->noChangeCount = 0;
		m->motionDelayCount = 0;
		return;
	}

	// 5. Backlash logika + „delay“ inicijavimas
	if ((pos < target - m->backlash || pos > target + m->backlash) || !*m->sensor.targetReached) {
		m->iface.enable();
		m->iface.start();
		*m->sensor.targetReached = false;

		if (m->motionDelayCount == 0)
		m->motionDelayCount = MOTION_DELAY_CYCLES;  // pvz. 25 ciklai ignoruoti "stuck" patikrà
	}

	// Soft delay
	if (m->motionDelayCount > 0) {
		m->motionDelayCount--;
		*m->sensor.lastPosition = filtered;
		return;
	}
	// -------------------------------------------

	// 6. Delta filtras
	if (delta > -deadband && delta < deadband)
	delta = 0;

	// 7. Uþstrigimo tikrinimas (leidþiamas tik kai delayCounter==0)
	if (pos < target - m->backlash) {
		if (delta < -deadband) {
			if (++m->stuckCount >= stuck_limit) {
				*m->sensor.faultFlag = true;
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
				*m->sensor.faultFlag = true;
				m->iface.stop();
				m->iface.disable();
			}
			} else if (delta < -deadband) {
			m->stuckCount = 0;
		}
	}

	// 8. Uþstrigimas vietoje
	if (delta == 0 && !*m->sensor.targetReached) {
		if (++m->noChangeCount >= stuck_limit) {
			*m->sensor.faultFlag = true;
			m->iface.stop();
			m->iface.disable();
		}
		} else {
		m->noChangeCount = 0;
	}

	// 9. Atnaujinimas
	*m->sensor.lastPosition = filtered;
}*/


void AutoMotorControl(MotorType motor)// v2
{
	MotorControlObj* m = motor ? &StepperMotorCtrl : &LinearMotorCtrl;

	uint8_t stuck_limit = STUCK_LIMIT;
	int16_t deadband = SENSOR_DEADBAND;

	int32_t pos = *m->sensor.position;
	int32_t target = *m->sensor.target;
	int32_t filtered = *m->sensor.positionFiltered;
	int32_t last = *m->sensor.lastPosition;
	int32_t delta = filtered - last;

	// 1. FO jungties klaida
	if (SensorData.FO_lost_connecton_fault) {
		m->iface.stop();
		m->iface.disable();
		return;
	}

	// 2. Kryptis
	bool dir = (pos < target);
	m->iface.set_direction(dir);

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

	// 8. Uþstrigimas vietoje
	if (delta == 0 && !*m->sensor.targetReached) {
		if (++m->noChangeCount >= stuck_limit) {
			*m->sensor.faultFlag = 3; //stuck (motor or sensor not spinning)
			m->iface.stop();
			m->iface.disable();
		}
		} else {
		m->noChangeCount = 0;
	}

	// 9. Atnaujinimas
	*m->sensor.lastPosition = filtered;
}

/*
void AutoMotorControl(MotorType motor)// v1
{
	MotorControlObj* m = motor ? &StepperMotorCtrl : &LinearMotorCtrl;

	uint8_t stuck_limit = motor ? STUCK_LIMIT * 3 : STUCK_LIMIT * 2;

	int16_t sensor_deadband = motor ? SENSOR_DEADBAND * 4 : SENSOR_DEADBAND;

	// 1. FO jungtis
	if (SensorData.FO_lost_connecton_fault) {
		m->iface.stop();
		m->iface.disable();
		return;
	}

	// 2. Kryptis pagal tikslà
	bool direction = (*m->sensor.position < *m->sensor.target); // 1 = forward, 0 = backward
	m->iface.set_direction(direction);

	// 3. Kraðtiniø jungikliø logika:
	//  - jei pasiektas end switch ir bandoma vaþiuoti toliau á ribà ? stabdom
	//  - jei pasiektas, bet bandoma vaþiuoti nuo ribos ? leidþiam
	bool atMin = *m->sensor.endswitchMin;
	bool atMax = *m->sensor.endswitchMax;

	if ((direction && atMax) || (!direction && atMin)) {
		// Bandom vaþiuoti á ribà ? stabdom
		m->iface.stop();
		m->iface.disable();

		// Laikom, kad pasiektas tikslas (jei tai tinkama kryptis)
		*m->sensor.targetReached = true;
		return;
	}

	// 4. Tikslas pasiektas
	if (*m->sensor.position == *m->sensor.target) {
		m->iface.stop();
		m->iface.disable();
		*m->sensor.faultFlag = false;
		*m->sensor.targetReached = true;
		m->stuckCount = 0;
		m->noChangeCount = 0;
		return;
	}

	// 5. Backlash logika
	bool inBacklash = (*m->sensor.position >= (*m->sensor.target - m->backlash)) &&
	(*m->sensor.position <= (*m->sensor.target + m->backlash));

	if (!inBacklash || !*m->sensor.targetReached) {
		m->iface.enable();
		m->iface.start();
		*m->sensor.targetReached = false;
	}

	// 6. Pokytis (delta)
	int32_t delta = (int32_t)(*m->sensor.positionFiltered) - (int32_t)(*m->sensor.lastPosition);
	if (delta > -sensor_deadband && delta < sensor_deadband) {
		delta = 0;
	}

	// 7. Uþstrigimo tikrinimas (neteisinga kryptis)
	if (*m->sensor.position < (*m->sensor.target - m->backlash)) {
		if (delta < -sensor_deadband && ++m->stuckCount >= stuck_limit) {
			*m->sensor.faultFlag = true;
			m->iface.stop();
			m->iface.disable();
			} else if (delta > sensor_deadband) {
			m->stuckCount = 0;
		}
		} else if (*m->sensor.position > (*m->sensor.target + m->backlash)) {
		if (delta > sensor_deadband && ++m->stuckCount >= stuck_limit) {
			*m->sensor.faultFlag = true;
			m->iface.stop();
			m->iface.disable();
			} else if (delta < -sensor_deadband) {
			m->stuckCount = 0;
		}
	}

	// 8. Uþstrigimas vietoje
	if (delta == 0 && !*m->sensor.targetReached) {
		if (++m->noChangeCount >= stuck_limit) {
			*m->sensor.faultFlag = true;
			m->iface.stop();
			m->iface.disable();
		}
		} else {
		m->noChangeCount = 0;
	}

	// 9. Atnaujinam paskutinæ reikðmæ
	*m->sensor.lastPosition = *m->sensor.positionFiltered;
}*/


void ManualMotorControl(MotorType motor){
	MotorControlObj* m = motor ? &StepperMotorCtrl : &LinearMotorCtrl; //choose motor control stepper or linear

	int16_t *joy_axis = (motor == MOTOR_STEPPER) ? &Joystick.X_Axis : &Joystick.Y_Axis; //choose joystick axis (for stepper - X axis, for linear Y axis)
	bool SwapStepDir = (motor == MOTOR_STEPPER) ? true : false; //swaping directions for stepper, and keep as usual for linear

/*
	if(*joy_axis == 0){ 
		m->iface.stop();
		m->iface.disable();		
	}
	else{	
		if(*joy_axis > ){
			if(*m->sensor.endswitchMax){ // if max end switch reached turn off motor
				m->iface.stop();
				m->iface.disable();
			}
			else{
				m->iface.enable(); //enabling driver
				m->iface.set_direction(SwapStepDir); //set direction (stepper 1, linear 0)
				m->iface.start(); // start generating pulses
			}

		}
		else{
		if(*m->sensor.endswitchMin){ // if max end switch reached turn off motor
			m->iface.stop();
			m->iface.disable();
		}
		else{
				m->iface.enable(); //enabling driver
				m->iface.set_direction(!SwapStepDir); // (stepper 0, linear 1)
				m->iface.start(); // start generating pulses
			}
		}
		
	}*/

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
				AutoMotorControl(MOTOR_LINEAR);
				AutoMotorControl(MOTOR_STEPPER);
			}
		}		
	}
}