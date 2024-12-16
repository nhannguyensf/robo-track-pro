/**************************************************************
* Class    : CSC-615-01 Fall 2024
* Name     : Nhan Nguyen
* Student ID: 923100929
* Github   : nhannguyensf
* Project  : Final Assignment - Line Following Robot
*
* File     : main.c
*
* Description:
*   Main program for the line-following robot. Integrates:
*     - PID controller for precise motor control.
*     - Line sensor module for detecting line positions.
*     - Motor control module for driving motors.
*   Features graceful termination with Ctrl+C signal handling.
**************************************************************/

#include <stdio.h>
#include <signal.h>
#include <unistd.h>
#include "motor_control.h"
#include "line_sensor.h"
#include "pid.h"

// PID Controller Constants
#define KP 40.0f           // Proportional gain
#define KI 0.0f           // Integral gain
#define KD 0.0f           // Derivative gain

// Constants
#define TARGET_POSITION 2.0f  // Center position for line (0-4 sensors, middle is 2)
#define BASE_SPEED 70         // Base motor speed (percentage of max PWM)
#define PID_OUTPUT_LIMIT 100  // Max output for PID controller

// Global variables
PIDController pid;                // PID Controller instance
volatile sig_atomic_t stop_flag;  // Flag for graceful termination
int base_speed = BASE_SPEED;      // Initial base speed (modifiable)
int last_known_side = 0;          // 0 = left, 1 = right

// Function to handle Ctrl+C signal
void handle_signal(int sig) {
    if (sig == SIGINT) {
        stop_flag = 1;
    }
}

// Setup function for initialization
void setup() {
    // Register signal handler for Ctrl+C
    signal(SIGINT, handle_signal);

    // Initialize modules
    motor_init();
    line_sensors_init();
    pid_init(&pid, KP, KI, KD, -PID_OUTPUT_LIMIT, PID_OUTPUT_LIMIT);

    printf("Line-following robot started. Press Ctrl+C to stop.\n");
}

// Main loop for the line-following logic
void loop() {
    int sensor_states[NUM_SENSORS] = {0};
    read_line_sensors(sensor_states);

    // Define weights for each sensor based on distance from the center
    const float SENSOR_WEIGHTS[NUM_SENSORS] = {3.0, 1.0, 0.0, 1.0, 3.0};

    // // Track the last known side of the line
    // if (sensor_states[0] == 1 || sensor_states[1] == 1) {
    //     last_known_side = 1;  // Line detected on the left
    // } else if (sensor_states[3] == 1 || sensor_states[4] == 1) {
    //     last_known_side = 0;  // Line detected on the right
    // }

    // Calculate weighted average position of the line
    float position = 0.0f;
    float total_weight = 0.0f;
    int active_sensors = 0;

    for (int i = 0; i < NUM_SENSORS; i++) {
        if (sensor_states[i] == 1) {  // Line detected
            position += i * SENSOR_WEIGHTS[i];
            total_weight += SENSOR_WEIGHTS[i];
            active_sensors++;
        }
    }

    if (active_sensors > 0 && total_weight > 0) {
        position /= total_weight;  // Weighted average position
    } else {
        position = TARGET_POSITION;  // Default to center if no line detected
    }

    // // Line lost recovery logic
    // if (active_sensors == 0) {
    //     printf("Line lost! Searching for the line...\n");

    //     // Turn based on the last known side of the line
    //     if (last_known_side == 0) {
    //         // Turn to the left
    //         motor_control(LEFT_MOTOR, -40);  // Reverse left motor
    //         motor_control(RIGHT_MOTOR, 40); // Forward right motor
    //         printf("Turning left to search for the line.\n");
    //     } else {
    //         // Turn to the right
    //         motor_control(LEFT_MOTOR, 40);  // Forward left motor
    //         motor_control(RIGHT_MOTOR, -40); // Reverse right motor
    //         printf("Turning right to search for the line.\n");
    //     }

    //     usleep(300000); // Turn for 300ms
    //     return;         // Skip the rest of the loop until the line is found
    // }

    // Compute PID correction
    float correction = pid_compute(&pid, TARGET_POSITION, position);

    // Calculate motor speeds based on correction
    int left_speed = BASE_SPEED - (int)correction;
    int right_speed = BASE_SPEED + (int)correction;

    // Clamp motor speeds to valid range (0-100)
    if (left_speed > 100) left_speed = 100;
    if (left_speed < 0) left_speed = 0;
    if (right_speed > 100) right_speed = 100;
    if (right_speed < 0) right_speed = 0;

    // Apply motor speeds
    motor_control(LEFT_MOTOR, left_speed);
    motor_control(RIGHT_MOTOR, right_speed);

    // Print debug information
    printf("Position: %.2f | Correction: %.2f | Base Speed: %d | Left Speed: %d | Right Speed: %d\n",
           position, correction, base_speed, left_speed, right_speed);

    usleep(50000);  // Delay 50ms
}

int main() {
    setup();

    // Main control loop
    while (!stop_flag) {
        loop();
    }

    // Graceful shutdown
    printf("\nTerminating program...\n");
    motor_stop(LEFT_MOTOR);
    motor_stop(RIGHT_MOTOR);
    printf("Motors stopped. Program exited cleanly.\n");

    return 0;
}
