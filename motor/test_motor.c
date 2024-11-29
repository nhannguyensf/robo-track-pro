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

#include "DEV_Config.h"
#include "PCA9685.h"
#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>

#define MOTOR_A_PWM PCA_CHANNEL_0
#define MOTOR_A_IN1 PCA_CHANNEL_1
#define MOTOR_A_IN2 PCA_CHANNEL_2

void motor_init() {
    if (DEV_ModuleInit()) {
        printf("Init failed\n");
        exit(1);
    }
    PCA9685_Init(0x40);
    PCA9685_SetPWMFreq(50);
}

void motor_control(int speed, int direction) {
    PCA9685_SetPwmDutyCycle(MOTOR_A_PWM, speed);
    if (direction == 1) {
        PCA9685_SetLevel(MOTOR_A_IN1, 1);
        PCA9685_SetLevel(MOTOR_A_IN2, 0);
    } else {
        PCA9685_SetLevel(MOTOR_A_IN1, 0);
        PCA9685_SetLevel(MOTOR_A_IN2, 1);
    }
}

void motor_stop() {
    PCA9685_SetPwmDutyCycle(MOTOR_A_PWM, 0);
    PCA9685_SetLevel(MOTOR_A_IN1, 0);
    PCA9685_SetLevel(MOTOR_A_IN2, 0);
}

int main() {
    motor_init();
    
    printf("Forward at 50%%\n");
    motor_control(50, 1);
    sleep(3);
    
    printf("Reverse at 50%%\n");
    motor_control(50, 0);
    sleep(3);
    
    printf("Stopping\n");
    motor_stop();
    
    DEV_ModuleExit();
    return 0;
}
