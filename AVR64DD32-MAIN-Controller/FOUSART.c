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
	if (strncmp(command, "00000000000000", 14) == 0) { //if elevation angle, azimuth angle, solar cells voltage and current = 0 meaning it is FO optic fault: bad signal
		SensorData.FO_bad_signal_fault = true; //exp. hard bended fo
	}
	else{
		const uint8_t lengths[] = {4, 4, 3, 3, 1, 2};
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

			for (uint8_t i = 0; i < 6; i++) {
				char token[10] = {0};

				memcpy(token, p, lengths[i]);
				token[lengths[i]] = '\0';

				switch (i) {
					case 0: SensorData.HPElevation   = (uint16_t)strtol(token, NULL, 16); break;
					case 1: SensorData.HPAzimuth     = (uint16_t)strtol(token, NULL, 16); break;
					case 2: SensorData.PVU         = (uint16_t)strtol(token, NULL, 16)/ U_I_Precizion; break;
					case 3: SensorData.PVI         = (uint16_t)strtol(token, NULL, 16)/ U_I_Precizion; break;
					case 4: EndSwitchesValue       = (uint8_t)strtol(token, NULL, 16); break; //common end switches value
				}

				p += lengths[i];
			}
			SensorData.Elevation = SensorData.HPElevation / Angle_Precizion;
			SensorData.Azimuth = SensorData.HPAzimuth / Angle_Precizion;
			//spliting end switch value to separate end switch value according to axis
			SensorData.ElMin = (EndSwitchesValue & 0x01) ? 1 : 0;
			SensorData.ElMax = (EndSwitchesValue & 0x02) ? 1 : 0;
			SensorData.AzMin = (EndSwitchesValue & 0x04) ? 1 : 0;
			SensorData.AzMax = (EndSwitchesValue & 0x08) ? 1 : 0;
			SensorData.FO_bad_signal_fault = false; //reset error
			SensorData.FO_data_fault = false; //reset error
			SensorData.FO_lost_signal_fault = false; //reset error

		}
		else{
			//uncomment if nedded
			//screen_write_formatted_text("data is corupted!", 1, ALIGN_CENTER); // bad crc
			SensorData.FO_data_fault = true;
		}	
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
	uint8_t timeout = 0;
	SensorData.FO_lost_signal_fault = false;

    while (1) {
        char c = USART1_readChar(); // Reading a character from USART

		if(SensorData.FO_lost_signal_fault){
			if (++timeout == CountForError_FO) { // Timeout condition if usart1 reading is halted
				SensorData.FO_lost_connecton_fault = true;
				break;
			}
		}
        if (start) {
			
            if (c == '>') { // If received data end symbol			
				start = 0;
				command[index] = '\0';
				index = 0;
				if (strcmp(command, SensorData.FreshDataPack) != 0){ //only if message is different
					FODataSplitter(command); // Execute the received command //comment when testing lines below
				}
				strcpy(SensorData.FreshDataPack, command); // prevents from same message data splitting
				break;
            } else if (index < MESSAGE_LENGTH_FO) {
                command[index++] = c; // Store received character in command array
            }
        }
        if (c == '<') { // If received data start symbol
            start = 1;
            index = 0;
        }
    }
}

