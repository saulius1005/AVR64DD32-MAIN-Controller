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
#define RS485_TIMEOUT_COUNTER 200000 ///< Timeout counter value for operations slower speed meaning more this
#define CountForError_RS485 3 //times to receive signal error and after this number will be set up connection fault
#define MESSAGE_LENGTH_RS485 16


typedef struct {
	uint16_t azimuth;
	uint16_t elevation;
	uint8_t windspeed;
	uint8_t winddirection;
	uint16_t lightlevel;
	bool WS_lost_connecton_fault;
	bool WS_lost_signal_fault;
	bool WS_data_fault;
} Wearther_Station;

extern Wearther_Station WSData;

#endif /* RS485USART_H_ */