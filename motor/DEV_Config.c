/***********************************************************************************************************************
 * File    : DEV_Config.c
 * Purpose : Implements GPIO, I2C, and SPI operations using multiple libraries (BCM2835, WiringPi, or custom DEV).
 * Modified: Nhan Nguyen
 ***********************************************************************************************************************/

#include "DEV_Config.h"
#include <unistd.h>
#include <fcntl.h>

// Global variables
uint32_t fd; // File descriptor for I2C or SPI
int INT_PIN; // Interrupt pin number

/***********************************************************************************************************************
 * GPIO Functions
 ***********************************************************************************************************************/

/**
 * @brief Configure GPIO pin as input or output.
 * @param Pin GPIO pin number.
 * @param Mode 0 for input, 1 for output.
 */
void DEV_GPIO_Mode(UWORD Pin, UWORD Mode) {
#ifdef USE_BCM2835_LIB
    bcm2835_gpio_fsel(Pin, (Mode == 0) ? BCM2835_GPIO_FSEL_INPT : BCM2835_GPIO_FSEL_OUTP);
#elif USE_WIRINGPI_LIB
    pinMode(Pin, (Mode == 0) ? INPUT : OUTPUT);
    if (Mode == 0) pullUpDnControl(Pin, PUD_UP); // Enable pull-up for input pins
#elif USE_DEV_LIB
    SYSFS_GPIO_Export(Pin);
    SYSFS_GPIO_Direction(Pin, (Mode == 0) ? SYSFS_GPIO_IN : SYSFS_GPIO_OUT);
#endif
}

/**
 * @brief Write a digital value to a GPIO pin.
 * @param Pin GPIO pin number.
 * @param Value 0 (LOW) or 1 (HIGH).
 */
void DEV_Digital_Write(UWORD Pin, UBYTE Value) {
#ifdef USE_BCM2835_LIB
    bcm2835_gpio_write(Pin, Value);
#elif USE_WIRINGPI_LIB
    digitalWrite(Pin, Value);
#elif USE_DEV_LIB
    SYSFS_GPIO_Write(Pin, Value);
#endif
}

/**
 * @brief Read the digital value from a GPIO pin.
 * @param Pin GPIO pin number.
 * @return 0 (LOW) or 1 (HIGH).
 */
UBYTE DEV_Digital_Read(UWORD Pin) {
#ifdef USE_BCM2835_LIB
    return bcm2835_gpio_lev(Pin);
#elif USE_WIRINGPI_LIB
    return digitalRead(Pin);
#elif USE_DEV_LIB
    return SYSFS_GPIO_Read(Pin);
#endif
}

/**
 * @brief Delay execution for a specified time.
 * @param xms Time in milliseconds.
 */
void DEV_Delay_ms(UDOUBLE xms) {
#ifdef USE_BCM2835_LIB
    bcm2835_delay(xms);
#elif USE_WIRINGPI_LIB
    delay(xms);
#elif USE_DEV_LIB
    for (UDOUBLE i = 0; i < xms; i++) usleep(1000); // 1 ms delay
#endif
}

/***********************************************************************************************************************
 * I2C Functions
 ***********************************************************************************************************************/

/**
 * @brief Initialize I2C communication with a specific slave address.
 * @param Add Slave address.
 */
void DEV_I2C_Init(uint8_t Add) {
#ifdef USE_BCM2835_LIB
    bcm2835_i2c_begin();
    bcm2835_i2c_setSlaveAddress(Add);
#elif USE_WIRINGPI_LIB
    fd = wiringPiI2CSetup(Add);
#elif USE_DEV_LIB
    DEV_HARDWARE_I2C_begin("/dev/i2c-1");
    DEV_HARDWARE_I2C_setSlaveAddress(Add);
#endif
}

/**
 * @brief Write a byte to the specified I2C command register.
 * @param Cmd Command register.
 * @param value Data to write.
 */
void I2C_Write_Byte(uint8_t Cmd, uint8_t value) {
#ifdef USE_BCM2835_LIB
    char wbuf[2] = {Cmd, value};
    bcm2835_i2c_write(wbuf, 2);
#elif USE_WIRINGPI_LIB
    wiringPiI2CWriteReg8(fd, Cmd, value);
#elif USE_DEV_LIB
    char wbuf[2] = {Cmd, value};
    DEV_HARDWARE_I2C_write(wbuf, 2);
#endif
}

/**
 * @brief Read a byte from the specified I2C command register.
 * @param Cmd Command register.
 * @return Data read.
 */
uint8_t I2C_Read_Byte(uint8_t Cmd) {
    uint8_t rbuf[1];
#ifdef USE_BCM2835_LIB
    bcm2835_i2c_read_register_rs((char *)&Cmd, (char *)rbuf, 1);
#elif USE_WIRINGPI_LIB
    rbuf[0] = wiringPiI2CReadReg8(fd, Cmd);
#elif USE_DEV_LIB
    DEV_HARDWARE_I2C_read(Cmd, (char *)rbuf, 1);
#endif
    return rbuf[0];
}

/**
 * @brief Read a 16-bit word from the specified I2C command register.
 * @param Cmd Command register.
 * @return 16-bit data read.
 */
uint16_t I2C_Read_Word(uint8_t Cmd) {
    uint8_t rbuf[2];
#ifdef USE_BCM2835_LIB
    bcm2835_i2c_read_register_rs((char *)&Cmd, (char *)rbuf, 2);
#elif USE_WIRINGPI_LIB
    rbuf[0] = wiringPiI2CReadReg16(fd, Cmd) & 0xFF;
    rbuf[1] = (wiringPiI2CReadReg16(fd, Cmd) >> 8) & 0xFF;
#elif USE_DEV_LIB
    DEV_HARDWARE_I2C_read(Cmd, (char *)rbuf, 2);
#endif
    return (rbuf[0] << 8) | rbuf[1];
}

/***********************************************************************************************************************
 * Module Initialization and Exit
 ***********************************************************************************************************************/

/**
 * @brief Initialize the hardware module.
 * @return 0 on success, 1 on failure.
 */
uint8_t DEV_ModuleInit(void) {
#ifdef USE_BCM2835_LIB
    return bcm2835_init() ? 0 : 1;
#elif USE_WIRINGPI_LIB
    return (wiringPiSetupGpio() < 0) ? 1 : 0;
#endif
    return 0;
}

/**
 * @brief Cleanup and close the hardware module.
 */
void DEV_ModuleExit(void) {
#ifdef USE_BCM2835_LIB
    bcm2835_i2c_end();
    bcm2835_close();
#elif USE_DEV_LIB
    DEV_HARDWARE_I2C_end();
#endif
}
