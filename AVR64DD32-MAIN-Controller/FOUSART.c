/*
 * FOUSART.c
 *
 * Created: 2025-09-05 11:22:04
 *  Author: Saulius
 */ 
#include "Settings.h"
#include "FOUSARTVar.h"

inline uint64_t hex2uint64(const char *p, uint8_t len) {
	uint64_t v = 0;
	for (uint8_t i = 0; i < len; i++) {
		v = (v << 4) | hexchar2val(p[i]);
	}
	return v;
}

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
	SensorData.ElMin = SensorData.ElMax = false;
	SensorData.AzMin = SensorData.AzMax = false;
	SensorData.FO_data_fault = false;
	SensorData.FO_bad_signal_fault = false;
	SensorData.FO_lost_signal_fault = false;

	const uint8_t lengths[] = {4, 4, 3, 3, 1};
	char temp[MESSAGE_LENGTH_FO - 2];

	// Split data and CRC
	strncpy(temp, command, MESSAGE_LENGTH_FO - 2);
	temp[MESSAGE_LENGTH_FO - 2] = '\0';
	uint64_t dataToCheck = hex2uint64(temp, MESSAGE_LENGTH_FO - 2);

	uint8_t crcToCheck = (uint8_t)strtol(command + MESSAGE_LENGTH_FO - 2, NULL, 16);

	bool crc_ok = crc8_cdma2000(dataToCheck) == crcToCheck ?  true : false;
	//uint8_t endSwitches = 0;

	// Detect “bad signal”
	if (strncmp(command, "00000000000000", 14) == 0) {
		SensorData.FO_bad_signal_fault = true;

		if (crc_ok) {
			char token[2];
			token[0] = command[14];
			token[1] = '\0';
			SensorData.endSwitches = (uint8_t)strtol(token, NULL, 16);
			} else {
			SensorData.FO_data_fault = true;
			return;
		}
	} else if (crc_ok) {
		// Parse all numeric tokens
		const char *p = command;
		char token[6]; // Enough for up to 5 hex chars + null terminator

		for (uint8_t i = 0; i < 5; i++) {
			memcpy(token, p, lengths[i]);
			token[lengths[i]] = '\0';
			p += lengths[i];

			switch (i) {
				case 0: SensorData.HPElevation = (uint16_t)strtol(token, NULL, 16); break;
				case 1: SensorData.HPAzimuth   = (uint16_t)strtol(token, NULL, 16); break;
				case 2: SensorData.PVU = (uint16_t)strtol(token, NULL, 16) / U_I_Precizion; break;
				case 3: SensorData.PVI = (uint16_t)strtol(token, NULL, 16) / U_I_Precizion; break;
				case 4: SensorData.endSwitches = (uint8_t)strtol(token, NULL, 16); break;
			}
		}

		SensorData.Elevation = SensorData.HPElevation / Angle_Precizion;
		SensorData.Azimuth   = SensorData.HPAzimuth   / Angle_Precizion;
		} else {
		SensorData.FO_data_fault = true;
		return;
	}

	// Common: update switch flags (executed for both valid and “bad signal” cases)
	SensorData.ElMin = (SensorData.endSwitches & 0x01);
	SensorData.ElMax = (SensorData.endSwitches & 0x02);
	SensorData.AzMin = (SensorData.endSwitches & 0x04);
	SensorData.AzMax = (SensorData.endSwitches & 0x08);
}

void FOReceiver() {
    uint8_t index = 0;
    char command[MESSAGE_LENGTH_FO] = {0}; // Empty command array
    uint8_t start = 0;
	SensorData.FO_lost_signal_fault = false;// usart1 while loop exit
	SensorData.FO_lost_connecton_fault = false; // while lop exit below

	RTC_ON(200);
		while (!(RTC.INTFLAGS & RTC_OVF_bm)) {
			char c = USART1_readCharRTC(); // Reading a character from USART

		if(SensorData.FO_lost_signal_fault){
				SensorData.FO_lost_connecton_fault = true;
				break;
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
	RTC.INTFLAGS = RTC_OVF_bm;
	RTC_OFF();
}


