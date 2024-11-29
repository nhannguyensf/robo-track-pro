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

#define MOTOR_B_PWM PCA_CHANNEL_3
#define MOTOR_B_IN1 PCA_CHANNEL_4
#define MOTOR_B_IN2 PCA_CHANNEL_5

void motor_init() {
    int result = DEV_ModuleInit();
    if (result) {
        printf("Init failed with error code: %d\n", result);
        exit(1);
    }
    
    PCA9685_Init(0x40);
    PCA9685_SetPWMFreq(50);
}

void motor_control(int motor, int speed) {
    int direction = (speed >= 0) ? 1 : 0;
    
    int abs_speed = abs(speed);
   
    if (abs_speed > 100) abs_speed = 100;
    
    if (motor == 1) {  // Motor A
        PCA9685_SetPwmDutyCycle(MOTOR_A_PWM, abs_speed);
        if (direction == 1) {
            PCA9685_SetLevel(MOTOR_A_IN1, 1);
            PCA9685_SetLevel(MOTOR_A_IN2, 0);
        } else {
            PCA9685_SetLevel(MOTOR_A_IN1, 0);
            PCA9685_SetLevel(MOTOR_A_IN2, 1);
        }
    } else if (motor == 2) {  // Motor B
        PCA9685_SetPwmDutyCycle(MOTOR_B_PWM, abs_speed);
        if (direction == 1) {
            PCA9685_SetLevel(MOTOR_B_IN1, 1);
            PCA9685_SetLevel(MOTOR_B_IN2, 0);
        } else {
            PCA9685_SetLevel(MOTOR_B_IN1, 0);
            PCA9685_SetLevel(MOTOR_B_IN2, 1);
        }
    }
}

void motor_stop(int motor) {
    if (motor == 1) {  // Motor A
        PCA9685_SetPwmDutyCycle(MOTOR_A_PWM, 0);
        PCA9685_SetLevel(MOTOR_A_IN1, 0);
        PCA9685_SetLevel(MOTOR_A_IN2, 0);
    } else if (motor == 2) {  // Motor B
        PCA9685_SetPwmDutyCycle(MOTOR_B_PWM, 0);
        PCA9685_SetLevel(MOTOR_B_IN1, 0);
        PCA9685_SetLevel(MOTOR_B_IN2, 0);
    }
}

int main() {
    motor_init();
    
    printf("Both motors forward at 50%%\n");
    motor_control(1, 50);   // Motor A forward
    motor_control(2, 50);   // Motor B forward
    sleep(3);
    
    printf("Stopping both motors\n");
    motor_stop(1);
    motor_stop(2);
    usleep(100000);

    printf("Motors in opposite directions\n");
    motor_control(1, -50);  // Motor A reverse
    motor_control(2, -50);  // Motor B reverse
    sleep(3);
    
    printf("Stopping both motors\n");
    motor_stop(1);
    motor_stop(2);
    
    DEV_ModuleExit();
    return 0;
}
