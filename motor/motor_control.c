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
