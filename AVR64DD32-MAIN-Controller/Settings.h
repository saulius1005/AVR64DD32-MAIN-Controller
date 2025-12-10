/*
 * Settings.h
 *
 * Created: 2024-12-04 17:00:49
 * Author: Saulius
 * 
 * @brief This header file contains function prototypes, macros, and includes necessary for configuring hardware,
 *        managing communication protocols (I2C, USART), and interacting with various sensors and peripherals.
 */

#ifndef SETTINGS_H_
#define SETTINGS_H_

#define DEVICE_ID_NUMBER 2

/**
 * @brief CPU clock frequency (F_CPU).
 * 
 * This macro defines the system clock frequency used for various calculations, including baud rate configuration.
 */
#define F_CPU 24000000

/**
 * @brief Macro for calculating the USART0 baud rate.
 * 
 * This macro calculates the baud rate for USART0 based on the desired baud rate and system clock (F_CPU).
 * 
 * @param BAUD_RATE Desired baud rate.
 * @return Calculated baud rate setting for USART0.
 */
#define USART0_BAUD_RATE(BAUD_RATE) ((float)(F_CPU * 64 / (8 *(float)BAUD_RATE)) + 0.5)

/**
 * @brief Macro for calculating the USART1 baud rate.
 * 
 * This macro calculates the baud rate for USART1 based on the desired baud rate and system clock (F_CPU).
 * 
 * @param BAUD_RATE Desired baud rate.
 * @return Calculated baud rate setting for USART1.
 */
#define USART1_BAUD_RATE(BAUD_RATE) ((float)(F_CPU * 64 / (8 *(float)BAUD_RATE)) + 0.5)

#include <avr/io.h>      /**< Include AVR I/O library for register definitions and hardware control */
#include <avr/cpufunc.h>
#include <util/delay.h>
#include <avr/interrupt.h> /**< Include AVR interrupt library for ISR (Interrupt Service Routine) support */
#include <stdio.h>       /**< Include standard I/O library for functions like printf */
#include <string.h>      /**< Include string library for handling string functions like strlen */
#include <stdlib.h>
#include <math.h>        /**< Include math library for mathematical functions (e.g., sin, cos) */
#include <float.h>       /**< Include float.h for floating point constants like FLT_MAX */
#include <stdbool.h>     /**< Include stdbool.h for boolean type support (true/false) */
#include <avr/pgmspace.h>
#include "i2c.h"
#include "SSD1306.h"
#include "windows.h"
#include "RS485LED.h"
#include "FOUSART.h"
#include "Joystick.h"
#include "RS485USART.h"
#include "LinearMotor.h"
#include "StepperMotor.h"
#include "Actions.h"

////////////////////////////////////////////////////////////////////////////////
// Function Prototypes
////////////////////////////////////////////////////////////////////////////////

/**
 * @brief Initializes the General Purpose I/O (GPIO) pins for necessary tasks.
 * 
 * This function configures the necessary GPIO pins for communication, control, 
 * or other I/O purposes. The exact configuration will depend on the application.
 */
void GPIO_init();

/**
 * @brief Initializes the external oscillator clock.
 * 
 * Configures the external oscillator for system clock usage.
 */
void CLOCK_XOSCHF_clock_init();

/**
 * @brief Initializes the external crystal oscillator.
 * 
 * Configures the external crystal for system clock usage.
 */
void CLOCK_XOSCHF_crystal_init();

void CLOCK_INHF_clock_init();

/**
 * @brief CRC decoder for CRC8 (Dallas/MAXIM).
 * 
 * Decodes a CRC-8 checksum for a given command.
 *
 * @param command 32-bit command value to decode the CRC.
 * @return CRC-8 checksum value.
 */
uint8_t CRC(uint32_t command);

/**
 * @brief Initializes the I2C bus for communication.
 * 
 * Configures the I2C peripheral to communicate with external devices.
 */
void I2C_init();

/**
 * @brief Transmits an address with read/write bit over I2C.
 * 
 * @param Add Address of the device.
 * @param Read Read or Write flag (1 for Read, 0 for Write).
 * @return 1 if successful, 0 if error.
 */
uint8_t TransmitAdd(uint8_t Add, uint8_t Read);

/**
 * @brief Reads one byte of data from the I2C bus.
 * 
 * @param ack Acknowledge flag.
 * @param data Pointer to store the read data.
 */
void ReadByteInf(uint8_t ack, uint8_t* data);

/**
 * @brief Transmits a byte of data over I2C.
 * 
 * @param Data Data byte to transmit.
 * @return 1 if successful, 0 if error.
 */
uint8_t TransmitByte(uint8_t Data);

/**
 * @brief Writes a byte of data to a register over I2C.
 * 
 * @param Add Address of the device.
 * @param Reg Register to write to.
 * @param Data Data to write.
 */
void WriteToReg(uint8_t Add, uint8_t Reg, uint8_t Data);

/**
 * @brief Reads a byte of data from a register over I2C.
 * 
 * @param Add Address of the device.
 * @param Reg Register to read from.
 * @return Data read from the register.
 */
uint8_t ReadReg(uint8_t Add, uint8_t Reg);

/**
 * @brief Writes multiple bytes of data to a register over I2C.
 * 
 * @param addr Address of the device.
 * @param reg Register to start writing.
 * @param data Data to write.
 * @param bytes Number of bytes to write.
 */
void WriteMulti(uint8_t addr, uint8_t reg, uint64_t data, uint8_t bytes);

/**
 * @brief Reads multiple bytes of data from a register over I2C.
 * 
 * @param addr Address of the device.
 * @param reg Register to start reading.
 * @param bytes Number of bytes to read.
 * @return Data read from the register.
 */
uint64_t ReadMulti(uint8_t addr, uint8_t reg, uint8_t bytes);

/**
 * @brief Initializes USART0 for serial communication.
 * 
 * Configures the USART0 for transmitting and receiving data.
 */
void USART0_init();

/**
 * @brief Sends a character over USART0.
 * 
 * @param c Character to send.
 */
void USART0_sendChar(char c);

/**
 * @brief Sends a string over USART0.
 * 
 * @param str String to send.
 */
void USART0_sendString(char *str);

/**
 * @brief USART0 character output function for printf.
 * 
 * @param c Character to send.
 * @param stream Stream for the output.
 * @return Character sent.
 */
int USART0_printChar(char c, FILE *stream);

/**
 * @brief Reads a character from USART0.
 * 
 * @return Character received.
 */
char USART0_readChar();

/**
 * @brief Initializes USART1 for serial communication.
 * 
 * Configures USART1 for transmitting and receiving data.
 */
void USART1_init();

/**
 * @brief Sends a character over USART1.
 * 
 * @param c Character to send.
 */
void USART1_sendChar(char c);

/**
 * @brief Sends a string over USART1.
 * 
 * @param str String to send.
 */
void USART1_sendString(char *str);

/**
 * @brief USART1 character output function for printf.
 * 
 * @param c Character to send.
 * @param stream Stream for the output.
 * @return Character sent.
 */
int USART1_printChar(char c, FILE *stream);

/**
 * @brief Reads a character from USART1.
 * 
 * @return Character received.
 */
char USART1_readChar();

/**
 * @brief Sends formatted data over USART.
 * 
 * @param usart_number USART port (0 or 1).
 * @param format Format string for the data.
 */
void USART_printf(uint8_t usart_number, const char *format, ...);

/**
 * @brief Initializes the ADC0 (Analog-to-Digital Converter).
 * 
 * Configures the ADC for reading analog signals.
 */
void ADC0_init();

void ADC0_SetupJoystick(uint8_t axis);

/**
 * @brief Reads data from ADC0.
 * 
 * @return ADC conversion result.
 */
uint16_t ADC0_read();


/**
 * @brief Initializes the screen.
 * 
 * This function initializes the screen, configuring the necessary hardware interfaces and settings
 * to prepare it for display operations.
 */
void screen_init();

/**
 * @brief Sends a command to the screen.
 * 
 * This function sends a specific command byte to the screen to control its behavior (e.g., to reset, 
 * adjust settings, or switch modes).
 * 
 * @param cmd The command byte to send to the screen.
 */
void screen_command(uint8_t cmd);

/**
 * @brief Sends data to the screen.
 * 
 * This function sends a data byte to the screen, typically to be displayed or used for rendering.
 * 
 * @param cmd The data byte to send to the screen.
 */
void screen_data(uint8_t cmd);

/**
 * @brief Draws an image on the screen.
 * 
 * This function draws an image on the screen based on the provided image data. The image is displayed
 * according to the specified mode.
 * 
 * @param mode The mode in which the image will be drawn (e.g., monochrome, color).
 * @param image_data Pointer to the image data to be displayed on the screen.
 */
void screen_draw_image(uint8_t mode, const uint8_t *image_data);

/**
 * @brief Draws a single character on the screen.
 * 
 * This function draws a character on the screen at the current position.
 * 
 * @param c The character to display.
 */
void screen_draw_char(char c);

/**
 * @brief Draws a string of text on the screen.
 * 
 * This function draws a string of text on the screen, ensuring that it fits within the specified maximum
 * length.
 * 
 * @param text Pointer to the null-terminated string to display.
 * @param max_length The maximum length of text to display.
 */
void screen_draw_text(char *text, uint8_t max_length);

/**
 * @brief Writes text to the screen at a specific line and pixel position.
 * 
 * This function writes text to the screen, starting from the specified line and pixel position.
 * 
 * @param text Pointer to the null-terminated string to display.
 * @param line The line number where the text should be written.
 * @param start_pixel The starting pixel position on the screen line.
 */
void screen_write_text(char *text, uint8_t line, uint8_t start_pixel);

/**
 * @brief Clears the screen.
 * 
 * This function clears the entire screen, typically by resetting all pixels to the background color.
 */
void screen_clear();

/**
 * @brief Adjusts the screen contrast.
 * 
 * This function adjusts the contrast of the screen to make the display more readable.
 * 
 * @param contrast The contrast level to set (typically a value between 0 and 255).
 */
void screen_contrast(uint8_t contrast);

/**
 * @brief Writes text to the screen with alignment on a specific line.
 * 
 * This function writes text to the screen, aligning it according to the specified alignment mode
 * (e.g., left, center, right).
 * 
 * @param text Pointer to the null-terminated string to display.
 * @param line The line number where the text should be written.
 * @param alignment The alignment mode to use (e.g., left, center, right).
 */
void screen_write_text_aligned(char *text, uint8_t line, alignment_t alignment);

/**
 * @brief Writes formatted text to the screen with alignment on a specific line.
 * 
 * This function writes formatted text to the screen, aligning it according to the specified alignment mode
 * (e.g., left, center, right). It supports variable arguments, allowing formatted text similar to printf.
 * 
 * @param format The format string for the text to display.
 * @param line The line number where the text should be written.
 * @param alignment The alignment mode to use (e.g., left, center, right).
 * @param ... The variable arguments for the format string.
 */
void screen_write_formatted_text(const char *format, uint8_t line, alignment_t alignment, ...);

/**
 * @brief Handles window-related operations.
 * 
 * This function manages windowing tasks, such as opening, closing, or resizing windows, depending on
 * the application context.
 */
void RS485_Led(RS485_LED_t LED);
uint8_t crc8_cdma2000(uint64_t data);
bool verify_crc8_cdma2000(uint64_t data_without_crc, uint8_t crc);
bool verify_crc8_cdma2000_v2(uint8_t *data, uint8_t crc);

void FOReceiver();

void ReadJoystickValues();
void LatchSwitcher();

void SelectWindow();

void RS485Receiver();

void TCA0_init_linear_PWM(uint16_t freq_hz, uint8_t duty_percent);
void LinearMotor_init();
void LinearMotor_enable();
void LinearMotor_disable();
void LinearMotor_start();
void LinearMotor_stop();
void LinearMotor_set_direction(bool dir);
uint16_t Read_LinearMotor_Voltage();
int16_t Read_LinearMotor_Current();
bool Read_LinearMotor_EF();

void TCD0_init_stepper_PWM(uint32_t freq_hz, uint8_t duty_percent);
void Stepper_init();
void Stepper_enable();
void Stepper_disable();
void Stepper_start();
void Stepper_stop();
void Stepper_set_direction(bool dir);
uint16_t Read_Stepper_Voltage();
int16_t Read_Stepper_Current();
bool Read_Stepper_PEND();
bool Read_Stepper_ALM();

uint16_t Read_MCU_Voltge();
void ADC0_SetupLinearMotor(uint8_t parameter);
void ADC0_SetupStepper(uint8_t parameter);

void work();

void AutoMotorControl(MotorType motor);

void windows();

uint8_t crc8_cdma2000_id(uint8_t device_id);

// Read a character from USART1 using RTC as timeout control
char USART0_readCharRTC();

char USART1_readCharRTC();

// Enable Real-Time Counter (RTC) with given period in milliseconds
void RTC_ON(uint16_t period_ms);

// Disable RTC
void RTC_OFF();

uint8_t hexchar2val(char c);

uint16_t hex2uint(const char *p, uint8_t len);

uint64_t hex2uint64(const char *p, uint8_t len);


#endif /* SETTINGS_H_ */