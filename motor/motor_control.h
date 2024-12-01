#ifndef MOTOR_CONTROL_H
#define MOTOR_CONTROL_H

#include "DEV_Config.h"
#include "PCA9685.h"

// Motor Definitions
#define LEFT_MOTOR_PWM PCA_CHANNEL_0
#define LEFT_MOTOR_IN1 PCA_CHANNEL_1
#define LEFT_MOTOR_IN2 PCA_CHANNEL_2
#define RIGHT_MOTOR_PWM PCA_CHANNEL_3
#define RIGHT_MOTOR_IN1 PCA_CHANNEL_4
#define RIGHT_MOTOR_IN2 PCA_CHANNEL_5

// Motor Identifiers
#define LEFT_MOTOR  1
#define RIGHT_MOTOR 2

// Function Prototypes
void motor_init(void);
void motor_control(int motor, int speed);
void motor_stop(int motor);

#endif // MOTOR_CONTROL_H
