/*
 * FOUSART.c
 *
 * Created: 2025-09-05 11:22:04
 *  Author: Saulius
 */ 
#include "Settings.h"
#include "FOUSARTVar.h"

void FODataSplitter(char *command) {
	const uint8_t lengths[] = {4, 4, 3, 3, 1, 2};
	const uint8_t count = sizeof(lengths) / sizeof(lengths[0]);

	const char *p = command;
	uint8_t EndSwitchesValue = 0,
			crc = 0;

	for (uint8_t i = 0; i < count; i++) {
		char token[10] = {0};

		memcpy(token, p, lengths[i]);
		token[lengths[i]] = '\0';

		switch (i) {
			case 0: SensorData.Elevation   = (uint16_t)strtol(token, NULL, 16); break;
			case 1: SensorData.Azimuth     = (uint16_t)strtol(token, NULL, 16); break;
			case 2: SensorData.PVU         = (uint16_t)strtol(token, NULL, 16); break;
			case 3: SensorData.PVI         = (uint16_t)strtol(token, NULL, 16); break;
			case 4: EndSwitchesValue       = (uint8_t)strtol(token, NULL, 16); break;
			case 5: crc					   = (uint8_t)strtol(token, NULL, 16); break;
		}

		p += lengths[i];
	}

	SensorData.ElMin = (EndSwitchesValue & 0x01) ? 1 : 0;
	SensorData.ElMax = (EndSwitchesValue & 0x02) ? 1 : 0;
	SensorData.AzMin = (EndSwitchesValue & 0x04) ? 1 : 0;
	SensorData.AzMax = (EndSwitchesValue & 0x08) ? 1 : 0;

	screen_write_formatted_text("%lx", 5, ALIGN_CENTER, (((uint64_t)SensorData.Elevation << 44) | ((uint64_t)SensorData.Azimuth << 28) | ((uint64_t)SensorData.PVU << 16) | ((uint32_t)SensorData.PVI << 4) | EndSwitchesValue));
	screen_write_formatted_text("%x", 6, ALIGN_CENTER, crc);
	screen_write_formatted_text("%x", 7, ALIGN_CENTER, verify_crc8_cdma2000(((uint64_t)SensorData.Elevation << 44) | ((uint64_t)SensorData.Azimuth << 28) | ((uint64_t)SensorData.PVU << 16) | ((uint32_t)SensorData.PVI << 4) | EndSwitchesValue, crc));
	
}

/**
 * @brief Main transceiver function.
 *
 * This function continuously reads incoming data via USART, processes the data, 
 * and executes the appropriate command. If an error occurs or a warning is set, 
 * it handles the corresponding state. The function handles both normal command 
 * processing and error recovery.
 */
void FOReceiver() {
    uint8_t index = 0;
    char command[MESSAGE_LENGTH] = {0}; // Empty command array
    uint8_t start = 0;

    while (1) {
        char c = USART1_readChar(); // Reading a character from USART

        if (Status.error) { // If an error is active
            //FODataSplitter("0"); // Execute command 0 for error handling
            Status.error = 0; // Reset error value
            Status.errorCounter = 0;
            break;
        }

        if (start) {
            if (c == '>') { // If received data end symbol
                start = 0;
               FODataSplitter(command); // Execute the received command //comment when testing lines below
				//screen_write_formatted_text("FO data:", 0, ALIGN_LEFT); //uncomment to testing purposes only
				//screen_write_formatted_text("%s", 3, ALIGN_RIGHT, command);
                index = 0;
                break;
            } else if (index < MESSAGE_LENGTH) {
                command[index++] = c; // Store received character in command array
            }
        }

        if (c == '<') { // If received data start symbol
            start = 1;
            index = 0;
            Status.error = 0; // Reset error state
            Status.errorCounter = 0; // Reset error counter
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