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
#define RS485_TIMEOUT_COUNTER 1000 ///< Timeout counter value for operations
#define CountForError_RS485 10
#define MESSAGE_LENGTH_RS485 27


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