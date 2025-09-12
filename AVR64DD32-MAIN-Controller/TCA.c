/*
 * TCA.c
 *
 * Created: 2025-09-09 15:54:27
 *  Author: Saulius
 */ 
#include "Settings.h"

void TCA0_init_linear_PWM(uint16_t freq_hz, uint8_t duty_percent) //Auto TCA prescaler selection, that give us Frequency range: ~366Hz - ~93kHz. TLE9201SG max 20kHz
{
	const uint16_t prescalers[] = {1, 2, 4, 8, 16, 64, 256, 1024};
	const uint8_t clk_select[] = {
		TCA_SINGLE_CLKSEL_DIV1_gc,
		TCA_SINGLE_CLKSEL_DIV2_gc,
		TCA_SINGLE_CLKSEL_DIV4_gc,
		TCA_SINGLE_CLKSEL_DIV8_gc,
		TCA_SINGLE_CLKSEL_DIV16_gc,
		TCA_SINGLE_CLKSEL_DIV64_gc,
		TCA_SINGLE_CLKSEL_DIV256_gc,
		TCA_SINGLE_CLKSEL_DIV1024_gc
	};

	uint8_t chosen_clk = 0;
	uint8_t period = 0;

	// surandam tinkamà prescaler
	for (uint8_t i = 0; i < 8; i++) {
		uint32_t f_timer = F_CPU / prescalers[i];
		uint32_t tmp_period = (f_timer / freq_hz) - 1;

		if (tmp_period <= 255 && tmp_period >= 1) {
			period = (uint8_t)tmp_period;
			chosen_clk = clk_select[i];
			break; // radom maþiausià tinkamà prescaler
		}
	}

	// duty skaièiavimas
	uint8_t duty = (uint32_t)period * duty_percent / 100;
	if (duty > period) duty = period;

	// konfigûracija
	PORTMUX.TCAROUTEA = PORTMUX_TCA0_PORTD_gc;  // WOx ant PORTD

	TCA0.SPLIT.CTRLD = TCA_SPLIT_SPLITM_bm;   // Split mode
	TCA0.SPLIT.CTRLB = TCA_SPLIT_HCMP0EN_bm;    // enable WO3 (HCMP0 ? PD3)

	TCA0.SPLIT.HPER  = period;
	TCA0.SPLIT.HCMP0 = duty;

	TCA0.SPLIT.CTRLA = chosen_clk | TCA_SPLIT_ENABLE_bm; // paleidþiam su pasirinktu prescaler
}
