/*
 * FOUSART.h
 *
 * Created: 2025-09-05 11:21:40
 *  Author: Saulius
 */ 


#ifndef FOUSART_H_
#define FOUSART_H_

/**
 * @brief Maximum count for consecutive errors before marking the system as faulty.
 */
#define FO_TIMEOUT_COUNTER 5000 ///< Timeout counter value for operations
#define CountForError_FO 10
#define Angle_Precizion 100 // 100 meaning exp. 360 degree 10 3600 (360,0), 1 36000 (360,00)
#define U_I_Precizion 1 // 10 meaning 24, 1 240 (24.0)
#define MESSAGE_LENGTH_FO 20


typedef struct {
	uint16_t Elevation;
	uint16_t HPElevation;
	uint16_t Azimuth;
	uint16_t PVU;
	uint16_t PVI;
	uint8_t ElMin;
	uint8_t ElMax;
	uint8_t AzMin;
	uint8_t AzMax;
	bool FO_fault;
	bool FO_data_fault;
} FOdata;

extern FOdata SensorData;

#endif /* FOUSART_H_ */