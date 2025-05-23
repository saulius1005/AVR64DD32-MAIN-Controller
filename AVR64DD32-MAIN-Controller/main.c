/*
 * Created: 2025-04-30 16:52:56
 * Author: Saulius
 */

#include "Settings.h"

int main(void)
{
    // Initialize system clock, GPIO, I2C, ADC, USART, and screen
    CLOCK_XOSCHF_clock_init();
    GPIO_init();
    I2C_init();
    ADC0_init();
    USART0_init();
    USART1_init();
    screen_init();
    screen_clear(); // Clear the screen
    while (1) 
    {

    }
}
