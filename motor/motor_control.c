/**************************************************************
* Class    : CSC-615-01 Fall 2024
* Name     : Nhan Nguyen
* Student ID: 923100929
* Github   : nhannguyensf
* Project  : Final Assignment - Motor Control Implementation
*
* File     : motor_control.c
*
* Description:
*   This file contains the implementation of motor control
*   functions using the WaveShare Motor Driver HAT and PCA9685
*   PWM controller. It includes:
*     - Initialization of the motor driver and PWM settings.
*     - Functions to control motor speed and direction.
*     - Functions to stop the motors.
*
* Functions:
*   - motor_init(): Initializes the motor driver and PWM controller.
*   - motor_control(motor, speed): Sets the speed and direction
*       of the specified motor (LEFT_MOTOR or RIGHT_MOTOR).
*   - motor_stop(motor): Stops the specified motor.
*
* Notes:
*   - The PCA9685 PWM frequency is set to 100 Hz.
*   - Ensure proper connections between the Raspberry Pi,
*     Motor Driver HAT, and motors.
**************************************************************/

#include "motor_control.h"
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

void motor_init() {
    int result = DEV_ModuleInit();
    if (result) {
        printf("Init failed with error code: %d\n", result);
        exit(1);
    }

    PCA9685_Init(0x40);
    PCA9685_SetPWMFreq(100);
}

void motor_control(int motor, int speed) {
    int direction = (speed >= 0) ? 1 : 0;
    int abs_speed = abs(speed);

    if (abs_speed > 100) abs_speed = 100;

    if (motor == LEFT_MOTOR) {  // Left Motor
        PCA9685_SetPwmDutyCycle(LEFT_MOTOR_PWM, abs_speed);
        PCA9685_SetLevel(LEFT_MOTOR_IN1, direction);
        PCA9685_SetLevel(LEFT_MOTOR_IN2, !direction);
    } else if (motor == RIGHT_MOTOR) {  // Right Motor
        PCA9685_SetPwmDutyCycle(RIGHT_MOTOR_PWM, abs_speed);
        PCA9685_SetLevel(RIGHT_MOTOR_IN1, direction);
        PCA9685_SetLevel(RIGHT_MOTOR_IN2, !direction);
    }
}

void motor_stop(int motor) {
    if (motor == LEFT_MOTOR) {  // Left Motor
        PCA9685_SetPwmDutyCycle(LEFT_MOTOR_PWM, 0);
        PCA9685_SetLevel(LEFT_MOTOR_IN1, 0);
        PCA9685_SetLevel(LEFT_MOTOR_IN2, 0);
    } else if (motor == RIGHT_MOTOR) {  // Right Motor
        PCA9685_SetPwmDutyCycle(RIGHT_MOTOR_PWM, 0);
        PCA9685_SetLevel(RIGHT_MOTOR_IN1, 0);
        PCA9685_SetLevel(RIGHT_MOTOR_IN2, 0);
    }
}
