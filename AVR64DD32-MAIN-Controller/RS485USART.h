/*
 * RS485USART.h
 *
 * Created: 2025-09-05 11:15:15
 *  Author: Saulius
 */ 


#ifndef RS485USART_H_
#define RS485USART_H_

/**
 * @brief Maximum count for consecutive errors before marking the system as faulty.
 */
#define CountForError_RS485 10

#define MESSAGE_LENGTH_RS485 27

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
} CommunicationRS485;

extern CommunicationRS485 Status_RS485;

typedef struct {
	uint16_t azimuth;
	uint16_t elevation;
	uint16_t topelevation;
	uint8_t windspeed;
	uint8_t winddirection;
	uint16_t lightlevel;
} Wearther_Station;

extern Wearther_Station WSData;

#endif /* RS485USART_H_ */