/*
 * RS485USARTVar.h
 *
 * Created: 2025-09-09 13:20:19
 *  Author: Saulius
 */ 


#ifndef RS485USARTVAR_H_
#define RS485USARTVAR_H_


CommunicationRS485 Status_RS485 = {
	.error = 0,           ///< Error flag, initialized to 0 (no error).
	.errorCounter = 0,    ///< Error counter, initialized to 0.
	.warning = 0,          ///< Warning flag, initialized to 0 (no warning).
	.communicationError = false
};

Wearther_Station WSData = {
	.azimuth = 0,
	.elevation = 0,
	.topelevation = 0,
	.windspeed = 0,
	.winddirection = 0,
	.lightlevel = 0
};

#endif /* RS485USARTVAR_H_ */