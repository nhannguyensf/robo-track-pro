#ifndef _DEV_CONFIG_H_
#define _DEV_CONFIG_H_

/***********************************************************************************************************************
 * File    : DEV_Config.h
 * Purpose : Provides function declarations and macros for GPIO, I2C, and SPI operations.
 * Modified: Nhan Nguyen
 ***********************************************************************************************************************/

#ifdef USE_BCM2835_LIB
    #include <bcm2835.h>  // BCM2835 library for GPIO and I2C
#elif USE_WIRINGPI_LIB
    #include <wiringPi.h> // WiringPi library for GPIO
    #include <wiringPiI2C.h> // WiringPi I2C support
#elif USE_DEV_LIB
    #include "sysfs_gpio.h" // System file GPIO interface
    #include "dev_hardware_i2c.h" // Custom I2C hardware abstraction
    #include "dev_hardware_SPI.h" // Custom SPI hardware abstraction
#endif

#include <stdint.h> // Standard integer definitions
#include "Debug.h"  // Debugging utilities
#include <errno.h>  // Error codes
#include <stdio.h>  // Standard I/O
#include <string.h> // String handling
#include <unistd.h> // POSIX API

// Define I2C and SPI modes
#define DEV_SPI 0
#define DEV_I2C 1

// Data type shortcuts for better readability
#define UBYTE   uint8_t
#define UWORD   uint16_t
#define UDOUBLE uint32_t

// GPIO Pin for Interrupt Handling
extern int INT_PIN; 

// Function Prototypes
uint8_t DEV_ModuleInit(void); // Initialize the hardware module
void DEV_ModuleExit(void);    // Cleanup and exit the hardware module

void DEV_I2C_Init(uint8_t Add);           // Initialize I2C communication
void I2C_Write_Byte(uint8_t Cmd, uint8_t value); // Write a byte over I2C
uint8_t I2C_Read_Byte(uint8_t Cmd);       // Read a byte over I2C
uint16_t I2C_Read_Word(uint8_t Cmd);      // Read a word (16-bit) over I2C

void DEV_GPIO_Mode(UWORD Pin, UWORD Mode); // Set GPIO pin mode
void DEV_Digital_Write(UWORD Pin, UBYTE Value); // Write digital output to a GPIO pin
UBYTE DEV_Digital_Read(UWORD Pin); // Read digital input from a GPIO pin

void DEV_Delay_ms(UDOUBLE xms); // Delay execution for a specified time in milliseconds

void DEV_SPI_WriteByte(UBYTE Value); // Write a byte over SPI
void DEV_SPI_Write_nByte(uint8_t *pData, uint32_t Len); // Write multiple bytes over SPI

#endif // _DEV_CONFIG_H_
