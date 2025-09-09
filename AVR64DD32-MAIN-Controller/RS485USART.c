/*
 * RS485USART.c
 *
 * Created: 2025-09-05 11:11:30
 *  Author: Saulius
 */ 
#include "Settings.h"

void RS485DataSplitter(char *command) {
	screen_write_formatted_text("%s", 0, ALIGN_CENTER, command);
}

void RS485Receiver() {
	uint8_t index = 0;
	char command[MESSAGE_LENGTH] = {0}; // Empty command array
	uint8_t start = 0;

	while (1) {
		char c = USART0_readChar(); // Reading a character from USART

		if (Status.error) { // If an error is active
			//FODataSplitter("0"); // Execute command 0 for error handling
			Status.error = 0; // Reset error value
			Status.errorCounter = 0;
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
				} else if (index < MESSAGE_LENGTH) {
				command[index++] = c; // Store received character in command array
			}
		}

		if (c == '{') { // If received data start symbol
			start = 1;
			index = 0;
			Status.error = 0; // Reset error state
			Status.errorCounter = 0; // Reset error counter
			RS485_Led(RX_LED_ON);
		}

		if (Status.warning) {
			Status.warning = 0;
			if (Status.errorCounter < CountForError) {
				Status.errorCounter++;
				} else {
				Status.error = 1; // Set error flag if too many warnings
			}
		}
	}
}