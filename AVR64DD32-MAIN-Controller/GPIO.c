/**
 * @file GPIO.c
 * @brief GPIO Initialization for various peripherals and sensors
 * 
 * Created: 2024-12-04 16:54:46
 * Author: Saulius
 */

#include "Settings.h"

void GPIO_init(){
    // Configure USART0 and USART1 pin routing
    PORTMUX.USARTROUTEA = PORTMUX_USART0_ALT1_gc | PORTMUX_USART1_ALT2_gc; // Set USART0 to alternative pins set 1, USART1 to alternative pins set 2
    PORTMUX.TWIROUTEA = PORTMUX_TWI0_DEFAULT_gc; // Set TWI0 to default pins

    // Configure Port A (PA) for RX LED, I2C SDA, SCL, USART0 TX, TX LED and XDIR
    PORTA.DIRSET = PIN2_bm | PIN3_bm | PIN4_bm | PIN6_bm | PIN7_bm; // Set PA2, PA3, PA4, PA7 as output (RX LED, I2C SDA, SCL, USART0 TX, TX LED, XDIR)
    PORTA.DIRCLR = PIN1_bm | PIN5_bm; // Set  PA1 as Joystick button,  PA5 as input (USART0 RX)
	PORTA.PIN1CTRL = PORT_PULLUPEN_bm; // Enable pull-up for PA1 (Joystick button)
    PORTA.PIN4CTRL = PORT_PULLUPEN_bm; // Enable pull-up for PA4 (I2C SCL)
    PORTA.PIN5CTRL = PORT_PULLUPEN_bm; // Enable pull-up for PA5 (USART0 RX)

    // Configure ADC pins for Joystick x and y axis
    PORTC.PIN1CTRL &= ~PORT_ISC_gm; // Disable interrupt sense for PC1 (X axis)
    PORTC.PIN1CTRL |= PORT_ISC_INPUT_DISABLE_gc; // Disable input sense for PC1
    //PORTC.PIN1CTRL &= ~PORT_PULLUPEN_bm; // Disable pull-up for PC1

    PORTC.PIN2CTRL &= ~PORT_ISC_gm; // Disable interrupt sense for PC2 (Y axis)
    PORTC.PIN2CTRL |= PORT_ISC_INPUT_DISABLE_gc; // Disable input sense for PC2
    //PORTC.PIN2CTRL &= ~PORT_PULLUPEN_bm; // Disable pull-up for PC2

	PORTC.DIRSET = PIN0_bm; //Set PC0 as RX LED

    // Configure Port D (PD) for USART1 TX and RX
    PORTD.DIRSET = PIN5_bm | PIN6_bm; //Set PD5 as output (Clock change command) and PD6 as output (USART1 TX)
	PORTD.OUTSET = PIN5_bm; // Set PD5 high (No action, to be controlled by software)
    PORTD.OUTCLR = PIN7_bm; // Set PD7 as input (USART1 RX)
    //PORTD.PIN6CTRL = PORT_PULLUPEN_bm; // Enable pull-up for PD6 (USART1 TX)
    //PORTD.PIN7CTRL = PORT_PULLUPEN_bm; // Enable pull-up for PD7 (USART1 RX)

    // Configure Port F (PF) for Keypad row and column control
    PORTF.DIRSET = PIN0_bm | PIN1_bm | PIN2_bm | PIN3_bm; // Set PF0, PF1, PF2, PF3 as output (Keypad rows)
    PORTF.OUTSET = PIN0_bm | PIN1_bm | PIN2_bm | PIN3_bm; // Set Keypad rows to high


}
