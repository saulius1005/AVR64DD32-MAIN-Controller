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
	uint64_t datatocheck = hex2uint64(command, MESSAGE_LENGTH_FO - 2);
	uint8_t crc_received = (uint8_t)strtol(command + MESSAGE_LENGTH_FO - 2, NULL, 16);
	bool crc_ok = verify_crc8_cdma2000(datatocheck, crc_received);
	if (strncmp(command, "00000000000000", 14) == 0) { //no answer from Top controller. This is answer from "Attiny212 light transceiver" (on the same pcb as main mcu)
		SensorData.FO_bad_signal_fault = true;
		if (crc_ok){
			SensorData.endSwitches = hex2uint(&command[14], 1); //answer will be only about azimuth end switches (X)
		} 
		else{
			SensorData.FO_data_fault = true;
			return;
		}
	} 
	else if (crc_ok){
		const char *p = command;
		SensorData.HPElevation = hex2uint(p, 4); p += 4;
		SensorData.HPAzimuth   = hex2uint(p, 4); p += 4;
		SensorData.PVU         = hex2uint(p, 3) / U_I_Precizion; p += 3;
		SensorData.PVI         = hex2uint(p, 3) / U_I_Precizion; p += 3;
		SensorData.endSwitches = hex2uint(p, 1); p += 1;
		SensorData.Elevation = SensorData.HPElevation / Angle_Precizion;
		SensorData.Azimuth   = SensorData.HPAzimuth   / Angle_Precizion;
	} 
	else{
		SensorData.FO_data_fault = true;
		return;
	}
	SensorData.ElMin = (SensorData.endSwitches & 0x01);// Common: update switch flags (executed for both valid and “bad signal” cases)
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
	RTC_ON(300);
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


