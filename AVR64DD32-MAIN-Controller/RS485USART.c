/*
 * RS485USART.c
 *
 * Created: 2025-09-05 11:11:30
 *  Author: Saulius
 */ 
#include "Settings.h"
#include "RS485USARTVar.h"


inline uint8_t hexchar2val(char c) {// Fastest ANCII HEX conversion to uint8_t (support  A-F a-f) one simbol
	if (c >= '0' && c <= '9') return c - '0';
	if (c >= 'A' && c <= 'F') return c - 'A' + 10;
	if (c >= 'a' && c <= 'f') return c - 'a' + 10;
	return 0;
}

inline uint16_t hex2uint(const char *p, uint8_t len) {//ANCII Hex up to 4 symbols converter
	uint16_t val = 0;
	for (uint8_t i = 0; i < len; i++) {
		val = (val << 4) | hexchar2val(p[i]);
	}
	return val;
}

void RS485DataSplitter(char *command) {
	const uint8_t data_len = MESSAGE_LENGTH_RS485 - 2;  //data length without crc
	uint8_t datatocheck[data_len / 2];
	for (uint8_t i = 0; i < data_len / 2; i++) //preparing data to check
		datatocheck[i] = hex2uint(&command[i*2], 2);
	uint8_t crc_received = hex2uint(&command[data_len], 2); //only crc

	if (!verify_crc8_cdma2000_v2(datatocheck, crc_received)) { //checking crc
		WSData.WS_data_fault = true;
		return;
	}
	const char *p = command + 2;// if crc ok removing id simbols

	WSData.azimuth       = hex2uint(p, 4) / Angle_Precizion; p += 4; //converting ancii hex into uint16_t, uint8_t
	WSData.elevation     = hex2uint(p, 4) / Angle_Precizion; p += 4;
	WSData.windspeed     = hex2uint(p, 2); p += 2;
	WSData.winddirection = hex2uint(p, 1); p += 1;
	WSData.lightlevel    = hex2uint(p, 3); p += 3;

	WSData.WS_data_fault = false;
	WSData.WS_lost_signal_fault = false;

	RS485_Led(TX_LED_ON); //sending answer
	USART_printf(0, "[%02x%04x%04x%03x%03x%x%03x%03x%03x%03x%02x]\r\n",
	(uint8_t)DEVICE_ID_NUMBER,
	(uint16_t)SensorData.HPElevation,
	(uint16_t)SensorData.HPAzimuth,
	(uint16_t)SensorData.PVU,
	(uint16_t)abs(SensorData.PVI),
	(uint8_t)SensorData.endSwitches,
	(uint16_t)StepperMotor.measuredVoltage,
	(uint16_t)abs(StepperMotor.measuredCurrent),
	(uint16_t)LinearMotor.measuredVoltage,
	(uint16_t)abs(LinearMotor.measuredCurrent),
	(uint8_t)crc8_cdma2000_id(DEVICE_ID_NUMBER)
	);
	RS485_Led(TX_LED_OFF);
}

uint8_t Early_ID_Check(char* command){
	return (uint8_t)strtol(command, NULL, 16);
}

void RS485Receiver() {
	uint8_t index = 0;
	char command[MESSAGE_LENGTH_RS485] = {0}; // Empty command array
	uint8_t start = 0;
	WSData.WS_lost_connecton_fault = false;
	WSData.WS_lost_signal_fault = false;
	RTC_ON(300); //tower should answer took about 3.5ms from WS sends data till answer end
	while (!(RTC.INTFLAGS & RTC_OVF_bm)) {
		char c = USART0_readCharRTC(); // Reading a character from USART
		if(WSData.WS_lost_signal_fault){
				WSData.WS_lost_connecton_fault = true;
				break;
		}
		if (start) {
			if (c == '}') {
			RS485_Led(RX_LED_OFF);
			start = 0;
			command[index] = '\0';
			index = 0;
			RS485DataSplitter(command);
			break;
		}
		else if (index < MESSAGE_LENGTH_RS485) {
			command[index++] = c;
			if (index == 2) { //check id first 2 simbols
				if (Early_ID_Check(command) != DEVICE_ID_NUMBER) {
					start = 0;//If id not match reseting all
					index = 0;
					RS485_Led(RX_LED_OFF);
					continue;
				}
			}
		}
		}
		if (c == '{') { // If received data start symbol
			start = 1;
			index = 0;
			RS485_Led(RX_LED_ON);
		}
	}
	RTC.INTFLAGS = RTC_OVF_bm;
	RTC_OFF();
}