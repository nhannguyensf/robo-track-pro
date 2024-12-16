/**************************************************************
* Class    : CSC-615-01 Fall 2024
* Name     : Nhan Nguyen
* Student ID: 923100929
* Github   : nhannguyensf
* Project  : Final Assignment - Motor Control Testing
*
* File     : test_motor.c

* Description:
*   This program tests motor functionality using the WaveShare
*   Motor Driver HAT and Pulse Width Modulation (PWM). It verifies
*   the ability to control motor speed, direction, and stopping
*   operations. The program includes tests for:
*     - Moving both motors forward at 50% speed.
*     - Stopping both motors momentarily.
*     - Moving motors in opposite directions at 50% speed.
*     - Running both motors backward at 100% speed.
*
* Setup:
*   Ensure the motors are connected to the Motor Driver HAT
*   and that the Raspberry Pi is properly configured with
*   the I2C interface enabled. The program uses the PCA9685
*   chip for PWM signal generation.
**************************************************************/

#include "motor_control.h"
#include <stdio.h>
#include <unistd.h>
#include <signal.h>

// Global flag for termination
volatile sig_atomic_t stop_flag = 0;

// Signal handler for Ctrl+C
void handle_signal(int sig) {
    if (sig == SIGINT) {
        stop_flag = 1; // Set the flag to stop the program
    }
}

int main() {
    // Register the signal handler for SIGINT
    signal(SIGINT, handle_signal);

    motor_init();

    printf("Both motors forward at 50%%\n");
    motor_control(LEFT_MOTOR, 50);   // Left motor forward
    motor_control(RIGHT_MOTOR, 50);  // Right motor forward
    sleep(3);

    if (stop_flag) goto exit_cleanly;

    printf("Stopping both motors\n");
    motor_stop(LEFT_MOTOR);
    motor_stop(RIGHT_MOTOR);
    usleep(100000);

    if (stop_flag) goto exit_cleanly;

    printf("Motors in opposite directions\n");
    motor_control(LEFT_MOTOR, 50);   // Left motor forward
    motor_control(RIGHT_MOTOR, -50); // Right motor reverse
    sleep(3);

    if (stop_flag) goto exit_cleanly;

    printf("Stopping both motors\n");
    motor_stop(LEFT_MOTOR);
    motor_stop(RIGHT_MOTOR);
    usleep(100000);

    if (stop_flag) goto exit_cleanly;

    printf("Both motors backward at 100%%\n");
    motor_control(LEFT_MOTOR, -100);  // Left motor backward
    motor_control(RIGHT_MOTOR, -100); // Right motor backward
    sleep(3);

    if (stop_flag) goto exit_cleanly;

    printf("Stopping both motors\n");
    motor_stop(LEFT_MOTOR);
    motor_stop(RIGHT_MOTOR);
    usleep(100000);

exit_cleanly:
    printf("\nTerminating program...\n");
    motor_stop(LEFT_MOTOR);
    motor_stop(RIGHT_MOTOR);
    DEV_ModuleExit(); // Clean up the device
    printf("Motors stopped. Program exited cleanly.\n");

    return 0;
}
