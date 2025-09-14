/*
 * Actions.h
 *
 * Created: 2025-09-13 20:03:59
 *  Author: Saulius
 */ 


#ifndef ACTIONS_H_
#define ACTIONS_H_

#define MIN_AZIMUTH 30
#define MAX_AZIMUTH 330
#define MAX_WIND 15
#define SAFE_ELEVATION 20
#define ELEVATION_BACKLASH 2
#define AZIMUTH_BACKLASH 5
#define MIN_LIGHT_LEVEL 300 // need to measure in real world, for now this.

typedef struct {
	uint16_t elevation;
	uint16_t azimuth;
} actions;

extern actions Target;



#endif /* ACTIONS_H_ */