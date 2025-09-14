/*
 * RS485USART.c
 *
 * Created: 2025-09-05 11:11:30
 *  Author: Saulius
 */ 
#include "Settings.h"
#include "RS485USARTVar.h"

void RS485DataSplitter(char *command) {
	uint16_t *fields[] = {
		&WSData.azimuth,
		&WSData.elevation,
		&WSData.topelevation,
		(uint16_t*)&WSData.windspeed,
		(uint16_t*)&WSData.winddirection,
		&WSData.lightlevel
	};

	char *token = strtok(command, "|");
	for (uint8_t i = 0; token != NULL && i < 6; i++) {
		*fields[i] = (uint16_t)strtol(token, NULL, 10);
		token = strtok(NULL, "|");
	}

}

void RS485Receiver() {
	uint8_t index = 0;
	char command[MESSAGE_LENGTH_RS485] = {0}; // Empty command array
	uint8_t start = 0;
	uint16_t timeout = RS485_TIMEOUT_COUNTER;

	while (1) {
		char c = USART0_readChar(); // Reading a character from USART	
		if (--timeout == 0) { // Timeout condition
			break;
		}
		if (start) {
			if (c == '}') { // If received data end symbol
				RS485_Led(RX_LED_OFF);
				start = 0;
				command[index] = '\0';
				index = 0;
				RS485DataSplitter(command); // Execute the received command //comment when testing lines below
				break;
				} else if (index < MESSAGE_LENGTH_RS485) {
				command[index++] = c; // Store received character in command array
			}
		}
		if (c == '{') { // If received data start symbol
			start = 1;
			index = 0;
			RS485_Led(RX_LED_ON);
		}
	}
}