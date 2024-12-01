/**************************************************************
* Class    : CSC-615-01 Fall 2024
* Name     : Nhan Nguyen
* Student ID: 923100929
* Github   : nhannguyensf
* Project  : Final Assignment - Main Program
*
* File     : main.c
*
* Description:
*   This program demonstrates basic motor control using the
*   WaveShare Motor Driver HAT and PCA9685 PWM controller. It
*   initializes the motor driver, moves both motors forward at
*   a specified speed, and then stops them.
*
* Instructions:
*   1. Ensure the Motor Driver HAT is connected to the Raspberry Pi.
*   2. Run this program to verify motor functionality.
*
* Notes:
*   - The PCA9685 is configured for a 100 Hz PWM frequency.
*   - Modify motor_control() calls to test additional functionality.
**************************************************************/

#include "motor/motor_control.h"
#include <stdio.h>
#include <unistd.h>

int main() {
    // Initialize the motor driver
    motor_init();

    // Control the left and right motors
    printf("Both motors moving forward at 75%% speed...\n");
    motor_control(LEFT_MOTOR, 75);   // Left motor forward
    motor_control(RIGHT_MOTOR, 75);  // Right motor forward
    sleep(3);

    // Stop the motors
    printf("Stopping both motors...\n");
    motor_stop(LEFT_MOTOR);
    motor_stop(RIGHT_MOTOR);
    sleep(1);

    // Clean up
    DEV_ModuleExit();
    return 0;
}
