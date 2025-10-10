/*
 * windows.h
 *
 * Created: 2025-01-26 23:35:38
 *  Author: Saulius
 */ 


#ifndef WINDOWS_H_
#define WINDOWS_H_

#define MAX_VARS 16

typedef struct {
	uint8_t window;
	uint8_t lastWindow;
	uint16_t lastValues[MAX_VARS];
} screenShow;

extern screenShow show;


#endif /* WINDOWS_H_ */