/**************************************************************
* Class    : CSC-615-01 Fall 2024
* Name     : Nhan Nguyen
* Student ID: 923100929
* Github   : nhannguyensf
* Project  : Final Assignment - PID Controller Implementation
*
* File     : pid.c
*
* Description:
*   This file implements the functions defined in pid.h for
*   the PID controller. It includes initialization, computation,
*   and resetting of the PID state.
**************************************************************/

#include "pid.h"

void pid_init(PIDController *pid, float kp, float ki, float kd, float min_output, float max_output) {
    pid->kp = kp;
    pid->ki = ki;
    pid->kd = kd;
    pid->prev_error = 0.0f;
    pid->integral = 0.0f;
    pid->max_output = max_output;
    pid->min_output = min_output;
}

float pid_compute(PIDController *pid, float setpoint, float measured_value) {
    float error = setpoint - measured_value;

    // Proportional term
    float p_term = pid->kp * error;

    // Integral term
    pid->integral += error;
    float i_term = pid->ki * pid->integral;

    // Derivative term
    float derivative = error - pid->prev_error;
    float d_term = pid->kd * derivative;

    // Save the current error as the previous error for the next cycle
    pid->prev_error = error;

    // Compute the output and clamp it to min/max limits
    float output = p_term + i_term + d_term;
    if (output > pid->max_output) {
        output = pid->max_output;
    } else if (output < pid->min_output) {
        output = pid->min_output;
    }

    return output;
}

void pid_reset(PIDController *pid) {
    pid->prev_error = 0.0f;
    pid->integral = 0.0f;
}
