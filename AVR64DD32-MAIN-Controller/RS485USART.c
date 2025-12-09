/*
 * RS485USART.c
 *
 * Created: 2025-09-05 11:11:30
 *  Author: Saulius
 */ 
#include "Settings.h"
#include "RS485USARTVar.h"


void RS485DataSplitter(char *command) {
	char temp[MESSAGE_LENGTH_RS485-1]; //data storage
	const uint8_t lengths[] = {4, 4, 2, 1, 3}; //tokens length without crc

	strncpy(temp, command, MESSAGE_LENGTH_RS485-2); //copy data without crc
	temp[MESSAGE_LENGTH_RS485-2] = '\0';

	uint8_t datatocheck[(MESSAGE_LENGTH_RS485-2)/2]={0};

	for (uint8_t i = 0; i < (MESSAGE_LENGTH_RS485-2)/2; i++) {
		char buf[3] = { temp[i * 2], temp[i * 2 + 1], '\0' }; // du simboliai + '\0'
		datatocheck[i] = (uint8_t)strtol(buf, NULL, 16);
	}
	strncpy(temp, command + (MESSAGE_LENGTH_RS485-2), 2); //copy only crc
	temp[2] = '\0';

	uint8_t crctocheck = (uint8_t)strtol(temp, NULL, 16); //convert char to int


	if(verify_crc8_cdma2000_v2(datatocheck, crctocheck)){ //if data valid update it
		//screen_write_formatted_text("data is correct", 1, ALIGN_CENTER);//uncomment if nedded// crc ok

		memmove(command, command + 2, strlen(command + 2) + 1); // removing id simbols

		const char *p = command;

		for (uint8_t i = 0; i < 5; i++) {
			char token[5] = {0}; //longest token length + 1

			memcpy(token, p, lengths[i]);
			token[lengths[i]] = '\0';

			switch (i) {

				case 0: WSData.azimuth   = (uint16_t)strtol(token, NULL, 16) / Angle_Precizion; break;
				case 1: WSData.elevation     = (uint16_t)strtol(token, NULL, 16) / Angle_Precizion; break;
				case 2: WSData.windspeed         = (uint8_t)strtol(token, NULL, 16); break;
				case 3: WSData.winddirection       = (uint8_t)strtol(token, NULL, 16); break;
				case 4: WSData.lightlevel	= (uint16_t)strtol(token, NULL, 16); break;
			}

			p += lengths[i];
		}
		WSData.WS_data_fault = false; //reset error
		WSData.WS_lost_signal_fault = false; //reset error
		//Sending answer
		RS485_Led(TX_LED_ON);
		USART_printf(0, "[%02x%04x%04x%03x%03x%x%03x%03x%03x%03x%02x]\r\n",
		(uint8_t)DEVICE_ID_NUMBER, //FF 0-255
		(uint16_t)SensorData.HPElevation, //FFFF 9000 (90.00)
		(uint16_t)SensorData.HPAzimuth, //FFFF 35999 (359.99)
		(uint16_t)SensorData.PVU, //FFF 2500 (250.0V)
		(uint16_t)abs(SensorData.PVI), //FFF 1100 (11.00A)
		(uint8_t)SensorData.endSwitches, //F 0-15
		(uint16_t)StepperMotor.measuredVoltage, //FFF 600 (60.0V)
		(uint16_t)abs(StepperMotor.measuredCurrent), //FFF 800 (8.00A)
		(uint16_t)LinearMotor.measuredVoltage, //FFF 240 (24.0V)
		(uint16_t)abs(LinearMotor.measuredCurrent), //FFF 600 (6.00A)
		(uint8_t)crc8_cdma2000_id(DEVICE_ID_NUMBER));
		RS485_Led(TX_LED_OFF);

	}
	else{
		//uncomment if nedded
		//screen_write_formatted_text("data is corupted!", 1, ALIGN_CENTER); // bad crc
		WSData.WS_data_fault = true;
	}

}

uint8_t Early_ID_Check(char* command){
	return (uint8_t)strtol(command, NULL, 16);
}

void RS485Receiver() {
	uint8_t index = 0;
	char command[MESSAGE_LENGTH_RS485] = {0}; // Empty command array
	uint8_t start = 0;
	//uint8_t timeout = 0;
	WSData.WS_lost_connecton_fault = false;
	WSData.WS_lost_signal_fault = false;

	RTC_ON(500); //tower should answer took about 3.5ms from WS sends data till answer end

	while (!(RTC.INTFLAGS & RTC_OVF_bm)) {
		char c = USART0_readCharRTC(); // Reading a character from USART

		if(WSData.WS_lost_signal_fault){
			//if (++timeout == CountForError_RS485) { // Timeout condition if usart1 reading is halted
				WSData.WS_lost_connecton_fault = true;
				break;
			//}
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
				if (index == 2){
					if(Early_ID_Check(command) != DEVICE_ID_NUMBER)
						break;
				}
				command[index++] = c; // Store received character in command array
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
/*
	while (1) {
		char c = USART0_readChar(); // Reading a character from USART	

		if(WSData.WS_lost_signal_fault){
			if (++timeout == CountForError_RS485) { // Timeout condition if usart1 reading is halted
				WSData.WS_lost_connecton_fault = true;
				break;
			}
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
	}*/
}