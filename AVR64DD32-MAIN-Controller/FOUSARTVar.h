/*
 * FOUSARTVar.h
 *
 * Created: 2025-09-05 11:22:35
 *  Author: Saulius
 */ 


#ifndef FOUSARTVAR_H_
#define FOUSARTVAR_H_


FOdata SensorData = {
	.Azimuth = 0,	//Azimuth sensor angle
	.Elevation = 0, //Elevation sensor angle
	.HPElevation = 0, //Elevation sensor angle high precizion value for sensor fault detection
	.HPAzimuth = 0,
	.PVU = 0, //Sun Panel Voltage
	.PVI = 0, //Sun Panel Current
	.ElMin = false,	//Separeted Elevation min End Switch value
	.ElMax = false,	//Separeted Elevation max End Switch value
	.AzMin = false,	//Separeted Azimuth min End Switch value
	.AzMax = false,	//Separeted Azimuth max End Switch value
	.FO_bad_signal_fault = false, // bad FO signal couses data to show  00000.... declaration at true if at MCU starts FO will not work its prevents from motors spinning (tries reach 0)
	.FO_lost_signal_fault = false, //if module not showing life (no power or MCU dead) 
	.FO_data_fault = false, // bad crc
	.FO_lost_connecton_fault = false,// true if usart1 while loop spins without receiving data, after 3 times repeting same error in a row seting up FO_no_power_fault in FO data receiving function (both resets after data receiving goes back (autoreset))
	.FO_elevation_sensor_fault = 0, 
	.FO_azimuth_sensor_fault = 0,
	.FO_faultcount = 0,
	.FreshDataPack = {"\0"}
};



#endif /* FOUSARTVAR_H_ */