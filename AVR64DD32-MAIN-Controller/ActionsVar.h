/*
 * ActionsVar.h
 *
 * Created: 2025-09-13 20:04:12
 *  Author: Saulius
 */ 


#ifndef ACTIONSVAR_H_
#define ACTIONSVAR_H_


actions Target = {
	.elevation = 30,
	.elevation_reached = true,
	.azimuth = 180
};

MotorControlObj LinearMotorCtrl = {
	.type = MOTOR_LINEAR,
	.iface = {
		.enable        = LinearMotor_enable,
		.disable       = LinearMotor_disable,
		.start         = LinearMotor_start,
		.stop          = LinearMotor_stop,
		.set_direction = LinearMotor_set_direction
	},
	.sensor = {
		.position        = &SensorData.Elevation,
		.positionFiltered= &SensorData.HPElevation,
		.faultFlag       = &SensorData.FO_elevation_sensor_fault,
		.lastPosition    = &Target.lastElevation,
		.target          = &Target.elevation,
		.targetReached   = &Target.elevation_reached
	},
	.stuckCount   = 0,
	.noChangeCount= 0,
	.backlash     = ELEVATION_BACKLASH
};

MotorControlObj StepperMotorCtrl = {
	.type = MOTOR_STEPPER,
	.iface = {
		.enable        = Stepper_enable,
		.disable       = Stepper_disable,
		.start         = Stepper_start,
		.stop          = Stepper_stop,
		.set_direction = Stepper_set_direction
	},
	.sensor = {
		.position        = &SensorData.Azimuth,
		.positionFiltered= &SensorData.HPAzimuth,
		.faultFlag       = &SensorData.FO_azimuth_sensor_fault,
		.lastPosition    = &Target.lastAzimuth,
		.target          = &Target.azimuth,
		.targetReached   = &Target.azimuth_reached
	},
	.stuckCount   = 0,
	.noChangeCount= 0,
	.backlash     = AZIMUTH_BACKLASH
};


#endif /* ACTIONSVAR_H_ */