/*
 * FOUSART.c
 *
 * Created: 2025-09-05 11:22:04
 *  Author: Saulius
 */ 
#include "Settings.h"
#include "FOUSARTVar.h"

uint64_t hexToUint64(const char *str) {
	uint64_t result = 0;
	char c;

	while ((c = *str++)) {
		result <<= 4; // kiekvienas hex simbolis = 4 bitai

		if (c >= '0' && c <= '9') {
			result |= (uint64_t)(c - '0');
			} else if (c >= 'A' && c <= 'F') {
			result |= (uint64_t)(c - 'A' + 10);
			} else if (c >= 'a' && c <= 'f') {
			result |= (uint64_t)(c - 'a' + 10);
			} else {
			// netinkamas simbolis
			return 0;
		}
	}
	return result;
}

void FODataSplitter(char *command) {
	const uint8_t lengths[] = {4, 4, 3, 3, 1, 2};
	const uint8_t count = sizeof(lengths) / sizeof(lengths[0]);
	char temp[16];

	strncpy(temp, command, 15);
	temp[15] = '\0';
	uint64_t datatocheck = hexToUint64(temp);
	strncpy(temp, command + 15, 2); 
	temp[2] = '\0';
	uint8_t crctocheck = (uint8_t)strtol(temp, NULL, 16);

	if(verify_crc8_cdma2000(datatocheck, crctocheck)){ //if data valid update it
		//screen_write_formatted_text("data is correct", 1, ALIGN_CENTER);//uncomment if nedded// crc ok
		const char *p = command;
		uint8_t EndSwitchesValue = 0;

		for (uint8_t i = 0; i < count; i++) {
			char token[10] = {0};

			memcpy(token, p, lengths[i]);
			token[lengths[i]] = '\0';

			switch (i) {
				case 0: SensorData.Elevation   = (uint16_t)strtol(token, NULL, 16); break;
				case 1: SensorData.Azimuth     = (uint16_t)strtol(token, NULL, 16); break;
				case 2: SensorData.PVU         = (uint16_t)strtol(token, NULL, 16); break;
				case 3: SensorData.PVI         = (uint16_t)strtol(token, NULL, 16); break;
				case 4: EndSwitchesValue       = (uint8_t)strtol(token, NULL, 16); break; //common end switches value
			}

			p += lengths[i];
		}
		//spliting end switch value to separate end switch value according to axis
		SensorData.ElMin = (EndSwitchesValue & 0x01) ? 1 : 0;
		SensorData.ElMax = (EndSwitchesValue & 0x02) ? 1 : 0;
		SensorData.AzMin = (EndSwitchesValue & 0x04) ? 1 : 0;
		SensorData.AzMax = (EndSwitchesValue & 0x08) ? 1 : 0;

	}
	else{
		//uncomment if nedded
		//screen_write_formatted_text("data is corupted!", 1, ALIGN_CENTER); // bad crc
	}	
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
    char command[MESSAGE_LENGTH_FO] = {0}; // Empty command array
    uint8_t start = 0;

    while (1) {
        char c = USART1_readChar(); // Reading a character from USART

        if (Status_FO.error) { // If an error is active
            //FODataSplitter("0"); // Execute command 0 for error handling
            Status_FO.error = 0; // Reset error value
            Status_FO.errorCounter = 0;
            break;
        }

        if (start) {
            if (c == '>') { // If received data end symbol
               start = 0;
			   command[index] = '\0';
               index = 0;
               FODataSplitter(command); // Execute the received command //comment when testing lines below
				//screen_write_formatted_text("FO data:", 0, ALIGN_LEFT); //uncomment to testing purposes only
				//screen_write_formatted_text("%s", 3, ALIGN_RIGHT, command);
                break;
            } else if (index < MESSAGE_LENGTH_FO) {
                command[index++] = c; // Store received character in command array
            }
        }

        if (c == '<') { // If received data start symbol
            start = 1;
            index = 0;
            Status_FO.error = 0; // Reset error state
            Status_FO.errorCounter = 0; // Reset error counter
        }

        if (Status_FO.warning) {
            Status_FO.warning = 0;
            if (Status_FO.errorCounter < CountForError_FO) {
                Status_FO.errorCounter++;
            } else {
                Status_FO.error = 1; // Set error flag if too many warnings
            }
        }
    }
}