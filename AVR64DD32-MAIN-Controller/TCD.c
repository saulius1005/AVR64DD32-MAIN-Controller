/**
 * @file TCD.c
 * @brief Functions for configuring and controlling Timer/Counter D (TCD) on the AVR64DD32 microcontroller.
 * 
 * @details This file includes functions to initialize TCD, control its on/off state,
 *          and configure it for PWM generation with adjustable frequency and duty cycle.
 * 
 * @author Saulius
 * @date 2025-01-09
 */

#include "Settings.h"

void TCD0_init_stepper_PWM(uint32_t freq_hz, uint8_t duty_percent) {

	// Calculate compare registers
	uint16_t cmpbclr = (F_CPU / (4 * freq_hz * 2)) - 1;
	uint16_t cmpaset = (uint16_t)(cmpbclr * (duty_percent / 100.0)) + 1;
	uint16_t cmpbset = cmpbclr - cmpaset - 1;

	// Set TCD compare registers
	TCD0.CMPBCLR = cmpbclr;
	TCD0.CMPBSET = cmpbset;
	TCD0.CMPASET = cmpaset;

	ccp_write_io((uint8_t *) &TCD0.FAULTCTRL, TCD_CMPCEN_bm); ///< Enable WOC on PF2
	TCD0.CTRLB = TCD_WGMODE_DS_gc; ///< Set waveform mode to double slope

	while (!(TCD0.STATUS & TCD_ENRDY_bm));

	// Ájungiam WOC iðëjimà
	TCD0.FAULTCTRL = TCD_CMPAEN_bm | TCD_CMPBEN_bm | TCD_CMPCEN_bm;

	// Paleidþiam su prescaler = 4
	TCD0.CTRLA = TCD_CLKSEL_CLKPER_gc | TCD_CNTPRES_DIV4_gc;


	// Palaukti, kol sinchronizuosis
	while (!(TCD0.STATUS & TCD_ENRDY_bm));
}