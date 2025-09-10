/*
 * FOUSARTVar.h
 *
 * Created: 2025-09-05 11:22:35
 *  Author: Saulius
 */ 


#ifndef FOUSARTVAR_H_
#define FOUSARTVAR_H_

/**
 * @brief Communication status structure.
 * 
 * This structure holds flags and counters used to track the status of the 
 * communication system. The structure includes the following fields:
 * 
 * - `.error`: A flag indicating if an error has occurred.
 * - `.errorCounter`: A counter that increments when warnings occur.
 * - `.warning`: A flag indicating if there is a warning.
 */
CommunicationFO Status_FO = {
    .error = 0,           ///< Error flag, initialized to 0 (no error).
    .errorCounter = 0,    ///< Error counter, initialized to 0.
    .warning = 0          ///< Warning flag, initialized to 0 (no warning).
};

FOdata SensorData = {
	.Azimuth = 0,	//Azimuth sensor angle
	.Elevation = 0, //Elevation sensor angle
	.HPElevation = 0, //Elevation sensor angle high precizion value for sensor fault detection
	.PVU = 0, //Sun Panel Voltage
	.PVI = 0, //Sun Panel Current
	.ElMin = 0,	//Separeted Elevation min End Switch value
	.ElMax = 0,	//Separeted Elevation max End Switch value
	.AzMin = 0,	//Separeted Azimuth min End Switch value
	.AzMax = 0	//Separeted Azimuth max End Switch value
};



#endif /* FOUSARTVAR_H_ */