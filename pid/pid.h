/**************************************************************
* Class    : CSC-615-01 Fall 2024
* Name     : Nhan Nguyen
* Student ID: 923100929
* Github   : nhannguyensf
* Project  : Final Assignment - PID Controller
*
* File     : pid.h
*
* Description:
*   This header file declares the structures and functions for
*   a PID controller used for precise motor control.
*
* Features:
*   - Configurable gains (kp, ki, kd).
*   - Error tracking and output computation.
*   - Reset function for reinitializing integral and previous error.
**************************************************************/

#ifndef PID_H
#define PID_H

typedef struct {
    float kp;          // Proportional gain
    float ki;          // Integral gain
    float kd;          // Derivative gain
    float prev_error;  // Previous error for derivative calculation
    float integral;    // Accumulated integral error
    float max_output;  // Maximum allowable output (limits PID output)
    float min_output;  // Minimum allowable output
} PIDController;

/**
 * @brief Initializes the PID controller with given gains and output limits.
 *
 * @param pid Pointer to the PIDController structure.
 * @param kp Proportional gain.
 * @param ki Integral gain.
 * @param kd Derivative gain.
 * @param min_output Minimum output limit for PID.
 * @param max_output Maximum output limit for PID.
 */
void pid_init(PIDController *pid, float kp, float ki, float kd, float min_output, float max_output);

/**
 * @brief Computes the PID output based on the setpoint and measured value.
 *
 * @param pid Pointer to the PIDController structure.
 * @param setpoint Desired target value.
 * @param measured_value Current value from sensors.
 * @return PID computed output value (limited between min_output and max_output).
 */
float pid_compute(PIDController *pid, float setpoint, float measured_value);

/**
 * @brief Resets the integral and previous error values of the PID controller.
 *
 * @param pid Pointer to the PIDController structure.
 */
void pid_reset(PIDController *pid);

#endif // PID_H
