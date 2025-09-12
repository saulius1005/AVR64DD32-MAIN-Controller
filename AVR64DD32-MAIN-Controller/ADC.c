/**
 * @file ADC.c
 * @brief Implementation of ADC initialization and setup functions.
 * @author Saulius
 * @date 2024-12-19
 */

#include "Settings.h"

/**
 * @brief Initializes the ADC0 module.
 *
 * Configures the ADC with the following settings:
 * - Accumulated sample count: 128
 * - Prescaler: Division by 4
 * - Resolution: 12-bit
 * - Enables the ADC.
 */
void ADC0_init() {
    ADC0.CTRLB = ADC_SAMPNUM_ACC128_gc; // 1 measurements
    ADC0.CTRLC = ADC_PRESC_DIV4_gc; // 24Mhz / 16 ADC speed
    ADC0.CTRLA = ADC_ENABLE_bm | ADC_RESSEL_12BIT_gc; // 12-bit resolution
}


void ADC0_SetupJoystick(uint8_t axis) {
    VREF.ADC0REF = VREF_REFSEL_VDD_gc;
    ADC0.MUXPOS = axis;

}

void ADC0_SetupLinearMotor(uint8_t parameter) {
	switch (parameter)
	{
		case 1: //I
			VREF.ADC0REF = VREF_REFSEL_4V096_gc; // up to 9,21A (if MCU Vcc== 4.096V)| 0A= 0.4096V| 4.096- 0.4096 = 3,6864V/0,4 = 9.21A | max current at normal working conditions for linear motor is ~4A			
			ADC0.MUXPOS = ADC_MUXPOS_AIN1_gc; //PD1
		break;
		default://U
			VREF.ADC0REF = VREF_REFSEL_2V048_gc; //AMC1311 full range is 2.0V for linear motor 2.0V = 30.0V (300k)
			ADC0.MUXPOS = ADC_MUXPOS_AIN31_gc; //PC3
	}

}

void ADC0_SetupStepper(uint8_t parameter) {
	switch (parameter)
	{
		case 1: //I
			VREF.ADC0REF = VREF_REFSEL_4V096_gc; // up to 9,21A (if MCU Vcc== 4.096V)| 0A= 0.4096V| 4.096- 0.4096 = 3,6864V/0,4 = 9.21A | max current at normal working conditions for stepper motor is ~6A
			ADC0.MUXPOS = ADC_MUXPOS_AIN16_gc; //PF0
		break;
		default://U
			VREF.ADC0REF = VREF_REFSEL_2V048_gc; //AMC1311 full range is 2.0V for stepper 2.0V = 71.0V (710k)
			ADC0.MUXPOS = ADC_MUXPOS_AIN6_gc; //PD6
	}

}

void ADC0_SetupSysVoltage(){
	VREF.ADC0REF = VREF_REFSEL_1V024_gc; // 1.024V = 4096| 1.024 = 10.24V|
	ADC0.MUXPOS = ADC_MUXPOS_VDDDIV10_gc; //5V = 0.5V
}


/**
 * @brief Reads a value from ADC0.
 *
 * Starts an ADC conversion and waits for the result. Clears the result-ready
 * flag after reading. If accumulation is enabled, the result is shifted
 * appropriately.
 *
 * @return The ADC conversion result as a 12-bit value.
 */
uint16_t ADC0_read() {
    ADC0.COMMAND = ADC_STCONV_bm; // Start conversion
    while (!(ADC0.INTFLAGS & ADC_RESRDY_bm)); // Wait until result is ready
    ADC0.INTFLAGS = ADC_RESRDY_bm; // Clear result ready flag
    return ADC0.RES >> 4; // Shift result if accumulation is over 16
}

uint16_t Read_MCU_Voltge(){
ADC0_SetupSysVoltage();
return ADC0_read()*0.25; //ADC value * 10.26V (full adc range) / 4096 (Full adc range steps) exp: 1856 * 0.25 = 464 (4.64V)
}
