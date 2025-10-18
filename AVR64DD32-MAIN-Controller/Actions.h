/*
 * Actions.h
 *
 * Created: 2025-09-13 20:03:59
 *  Author: Saulius
 */ 


#ifndef ACTIONS_H_
#define ACTIONS_H_

#define MIN_AZIMUTH 30
#define MAX_AZIMUTH 330
#define MIN_ELEVATION 0
#define MAX_ELEVATION 90
#define MAX_WIND 15
#define SAFE_ELEVATION 20
#define MIN_LIGHT_LEVEL 300 // need to measure in real world, for now this.

#define ELEVATION_BACKLASH 2 //2.00 degree
#define AZIMUTH_BACKLASH 4 // 4.00 degree
#define SENSOR_DEADBAND 50   // maþiausias pokytis, kurá laikome tikru judesiu exp. 20=0.02 degree
#define STUCK_LIMIT 4      // ciklø skaièius prieð fault

typedef struct {
	uint16_t elevation;
	bool elevation_reached;
	uint16_t lastElevation;
	uint16_t azimuth;
	bool azimuth_reached;
	uint16_t lastAzimuth;
} actions;

extern actions Target;

// ---- MOTOR INTERFACE ---- //common for both motors only
typedef struct {
	void (*enable)(void);
	void (*disable)(void);
	void (*start)(void);
	void (*stop)(void);
	void (*set_direction)(bool dir);
	uint16_t (*read_voltage)(void);
	int16_t (*read_current)(void);

} MotorInterface;

typedef struct {
    uint16_t* position;          // pvz. SensorData.Elevation arba SensorData.Azimuth
    uint16_t* positionFiltered;  // pvz. SensorData.HPElevation arba SensorData.HPAzimuth
    bool*     faultFlag;         // pvz. SensorData.FO_elevation_sensor_fault
    uint16_t* lastPosition;      // pvz. Target.lastElevation arba Target.lastAzimuth
    uint16_t* target;            // pvz. Target.elevation arba Target.azimuth
    bool*     targetReached;     // pvz. Target.elevation_reached arba Target.azimuth_reached
	bool* endswitchMin;
	bool* endswitchMax;
} SensorInterface;

// ---- MOTOR TYPE ENUM ----
typedef enum {
	MOTOR_LINEAR,
	MOTOR_STEPPER
} MotorType;

// ---- MOTOR OBJECT ----
typedef struct {
	MotorType type;
	MotorInterface iface;
	SensorInterface sensor;
	uint8_t stuckCount;
	uint8_t noChangeCount;
	int32_t backlash;
	uint16_t* voltage;
	int16_t* current; 
} MotorControlObj;

extern MotorControlObj LinearMotorCtrl;
extern MotorControlObj StepperMotorCtrl;

#endif /* ACTIONS_H_ */