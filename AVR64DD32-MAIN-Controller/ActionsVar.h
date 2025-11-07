/*
 * ActionsVar.h
 *
 * Created: 2025-09-13 20:04:12
 *  Author: Saulius
 */ 


#ifndef ACTIONSVAR_H_
#define ACTIONSVAR_H_


actions Target = {
	.elevation = 37, //default elevation angle. This value are shown when no comunication from Weather station
	.elevation_reached = true,
	.lastElevation = 0,
	.azimuth = 171, //default azimuth angle. This value are shown when no comunication from Weather station
	.azimuth_reached = true,
	.lastAzimuth = 0
};

MotorControlObj LinearMotorCtrl = {
	.type = MOTOR_LINEAR,
	.iface = {
		.enable        = LinearMotor_enable,
		.disable       = LinearMotor_disable,
		.start         = LinearMotor_start,
		.stop          = LinearMotor_stop,
		.set_direction = LinearMotor_set_direction,
		.read_voltage  = Read_LinearMotor_Voltage,
		.read_current  = Read_LinearMotor_Current,

	},
	.sensor = {
		.position        = &SensorData.Elevation,
		.positionFiltered= &SensorData.HPElevation,
		.faultFlag       = &SensorData.FO_elevation_sensor_fault,
		.lastPosition    = &Target.lastElevation,
		.target          = &Target.elevation,
		.targetReached   = &Target.elevation_reached,
		.endswitchMin	 = &SensorData.ElMin,
		.endswitchMax	 = &SensorData.ElMax
	},
	.stuckCount   = 0,
	.noChangeCount= 0,
	.backlash     = ELEVATION_BACKLASH,
	.voltage	  = &LinearMotor.measuredVoltage,
	.current	  = &LinearMotor.measuredCurrent,
	.startDelay = 0
};

MotorControlObj StepperMotorCtrl = {
	.type = MOTOR_STEPPER,
	.iface = {
		.enable        = Stepper_enable,
		.disable       = Stepper_disable,
		.start         = Stepper_start,
		.stop          = Stepper_stop,
		.set_direction = Stepper_set_direction,
		.read_voltage  = Read_Stepper_Voltage,
		.read_current  = Read_Stepper_Current
	},
	.sensor = {
		.position        = &SensorData.Azimuth,
		.positionFiltered= &SensorData.HPAzimuth,
		.faultFlag       = &SensorData.FO_azimuth_sensor_fault,
		.lastPosition    = &Target.lastAzimuth,
		.target          = &Target.azimuth,
		.targetReached   = &Target.azimuth_reached,
		.endswitchMin	 = &SensorData.AzMin,
		.endswitchMax	 = &SensorData.AzMax
	},
	.stuckCount   = 0,
	.noChangeCount= 0,
	.backlash     = AZIMUTH_BACKLASH,
	.voltage	  = &StepperMotor.measuredVoltage,
	.current	  = &StepperMotor.measuredCurrent,
	.startDelay = 0
};


#endif /* ACTIONSVAR_H_ */