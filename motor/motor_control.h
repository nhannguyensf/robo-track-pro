/**************************************************************
* Class    : CSC-615-01 Fall 2024
* Name     : Nhan Nguyen
* Student ID: 923100929
* Github   : nhannguyensf
* Project  : Final Assignment - Motor Control Header
*
* File     : motor_control.h
*
* Description:
*   This header file declares the functions and constants required
*   for controlling motors using the WaveShare Motor Driver HAT
*   and PCA9685 PWM controller. It provides the interface for:
*     - Initializing the motor driver and PWM controller.
*     - Controlling motor speed and direction.
*     - Stopping the motors.
*
* Definitions:
*   - Motor Pins (PWM and control pins for LEFT_MOTOR and RIGHT_MOTOR).
*   - Motor Identifiers (LEFT_MOTOR and RIGHT_MOTOR).
*
* Function Prototypes:
*   - motor_init(): Initializes the motor driver and PWM controller.
*   - motor_control(motor, speed): Sets the speed and direction
*       of the specified motor.
*   - motor_stop(motor): Stops the specified motor.
*
* Notes:
*   - Ensure this file is included in programs requiring motor control.
*   - The PCA9685 is configured for 100 Hz PWM frequency.
**************************************************************/

#ifndef MOTOR_CONTROL_H
#define MOTOR_CONTROL_H

#include "DEV_Config.h"
#include "PCA9685.h"

// Motor Definitions
#define LEFT_MOTOR_PWM PCA_CHANNEL_5
#define LEFT_MOTOR_IN1 PCA_CHANNEL_3
#define LEFT_MOTOR_IN2 PCA_CHANNEL_4
#define RIGHT_MOTOR_PWM PCA_CHANNEL_0
#define RIGHT_MOTOR_IN1 PCA_CHANNEL_2
#define RIGHT_MOTOR_IN2 PCA_CHANNEL_1

// Motor Identifiers
#define LEFT_MOTOR  1
#define RIGHT_MOTOR 2

// Function Prototypes
void motor_init(void);
void motor_control(int motor, int speed);
void motor_stop(int motor);

#endif // MOTOR_CONTROL_H
