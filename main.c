/**************************************************************
* Class    : CSC-615-01 Fall 2024
* Name     : Nhan Nguyen
* Student ID: 923100929
* Github   : nhannguyensf
* Project  : Final Assignment - Line Following Robot with Obstacle Detection
*
* File     : main.c
*
* Description:
*   Main program for the line-following robot. Integrates:
*     - PID controller for precise motor control.
*     - Line sensor module for detecting line positions.
*     - Motor control module for driving motors.
*     - Echo sensors for obstacle detection.
*   Features graceful termination with Ctrl+C signal handling.
**************************************************************/

#include <stdio.h>
#include <signal.h>
#include <unistd.h>
#include "motor_control.h"
#include "line_sensor.h"
#include "pid.h"
#include "echo_sensor.h"

// PID Controller Constants
#define KP 20.0f           // Proportional gain
#define KI 0.0f            // Integral gain
#define KD 0.0f            // Derivative gain

// Constants
#define TARGET_POSITION 2.0f  // Center position for line (0-4 sensors, middle is 2)
#define BASE_SPEED 70         // Base motor speed (percentage of max PWM)
#define PID_OUTPUT_LIMIT 100  // Max output for PID controller
#define OBSTACLE_THRESHOLD 20.0f // Distance in cm to stop for obstacle

// Global variables
PIDController pid;                // PID Controller instance
volatile sig_atomic_t stop_flag;  // Flag for graceful termination

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
    echo_sensors_init();

    printf("Line-following robot with obstacle detection started. Press Ctrl+C to stop.\n");
}

// Function to check for obstacles
int check_for_obstacles() {
    float distances[NUM_ECHO_SENSORS] = {0};
    read_echo_sensors(distances);

    // Check the three front sensors (indices 1, 2, and 3)
    for (int i = 1; i <= 3; i++) {
        if (distances[i] > 0 && distances[i] < OBSTACLE_THRESHOLD) {
            printf("Obstacle detected by sensor %d at %.2f cm. Stopping!\n", i, distances[i]);
            return 1; // Obstacle detected
        }
    }
    return 0; // No obstacles
}

// Main loop for the line-following logic
void loop() {
    int sensor_states[NUM_SENSORS] = {0};
    read_line_sensors(sensor_states);

    // Define weights for each sensor based on distance from the center
    const float SENSOR_WEIGHTS[NUM_SENSORS] = {3.0, 1.0, 0.0, 1.0, 3.0};

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
    if (active_sensors == 0) {
        return;
    }

    if (active_sensors > 0 && total_weight > 0) {
        position /= total_weight;  // Weighted average position
    } else {
        position = TARGET_POSITION;  // Default to center if no line detected
    }

    // Check for obstacles
    if (check_for_obstacles()) {
        motor_stop(LEFT_MOTOR);
        motor_stop(RIGHT_MOTOR);
        usleep(500000); // Wait half a second to reevaluate
        return; // Skip the rest of the loop if an obstacle is detected
    }

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
           position, correction, BASE_SPEED, left_speed, right_speed);

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
