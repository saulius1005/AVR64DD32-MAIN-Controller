/*
 * RS485USARTVar.h
 *
 * Created: 2025-09-09 13:20:19
 *  Author: Saulius
 */ 


#ifndef RS485USARTVAR_H_
#define RS485USARTVAR_H_

Wearther_Station WSData = {
	.azimuth = 0,
	.elevation = 0,
	.topelevation = 0,
	.windspeed = 0,
	.winddirection = 0,
	.lightlevel = 0,
	.WS_lost_connecton_fault = false,
	.WS_lost_signal_fault = false,
	.WS_data_fault = false
};

#endif /* RS485USARTVAR_H_ */