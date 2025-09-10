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
#define CountForError_FO 10
#define Angle_Precizion 100 // 100 meaning exp. 360 degree 10 3600 (360,0), 1 36000 (360,00)
#define U_I_Precizion 10 // 10 meaning 24, 1 240 (24.0)

#define MESSAGE_LENGTH_FO 17

/**
 * @brief Structure to hold communication status.
 *
 * This structure is used to track the state of communication for the transceiver. 
 * It includes flags and counters to handle errors and warnings.
 */
typedef struct {
    uint8_t error;         /**< Error flag (1 if an error occurs, 0 otherwise) */
    uint8_t errorCounter;  /**< Counter for error occurrences */
    uint8_t warning;       /**< Warning flag (1 if a warning occurs) */
} CommunicationFO;

/**
 * @brief Global variable for tracking communication status.
 *
 * This external variable is used to store the current communication status, 
 * including error and warning states.
 */
extern CommunicationFO Status_FO;

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
} FOdata;

extern FOdata SensorData;

#endif /* FOUSART_H_ */