/**************************************************************
* Class:: CSC-615-01 Fall 2024
* Name:: Nhan Nguyen
* Student ID:: 923100929
* Github-Name:: nhannguyensf
* Project:: Assignment 3 - Motors & Motor Driver HAT
*
* File:: assignment3.c
*
* Description:: This program controls a motor using the WaveShare
*               Motor Driver HAT with Pulse Width Modulation (PWM).
*               The motor can stop, go forward, backward, and have
*               speed control. The program waits for a button press
*               to start, then runs the motor forward at 100% for 
*               2 seconds, gradually slows to 15%, stops for 2 second, 
*               and then gradually accelerates in reverse to 100%.
*               The setup uses the I2C interface and is connected 
*               to a Raspberry Pi using the PCA9685 chip for PWM.
**************************************************************/

#include "motor_control.h"
#include <stdio.h>
#include <unistd.h>

int main() {
    motor_init();

    printf("Both motors forward at 50%%\n");
    motor_control(LEFT_MOTOR, 50);   // Left motor forward
    motor_control(RIGHT_MOTOR, 50);  // Right motor forward
    sleep(3);

    printf("Stopping both motors\n");
    motor_stop(LEFT_MOTOR);
    motor_stop(RIGHT_MOTOR);
    usleep(100000);

    printf("Motors in opposite directions\n");
    motor_control(LEFT_MOTOR, 50);   // Left motor forward
    motor_control(RIGHT_MOTOR, -50); // Right motor reverse
    sleep(3);

    printf("Stopping both motors\n");
    motor_stop(LEFT_MOTOR);
    motor_stop(RIGHT_MOTOR);
    usleep(100000);

    printf("Both motors backward at 100%%\n");
    motor_control(LEFT_MOTOR, -100);  // Left motor backward
    motor_control(RIGHT_MOTOR, -100); // Right motor backward
    sleep(3);

    printf("Stopping both motors\n");
    motor_stop(LEFT_MOTOR);
    motor_stop(RIGHT_MOTOR);
    usleep(100000);

    DEV_ModuleExit();
    return 0;
}
