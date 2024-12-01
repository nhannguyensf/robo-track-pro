/**************************************************************
* Class    : CSC-615-01 Fall 2024
* Name     : Nhan Nguyen
* Student ID: 923100929
* Github   : nhannguyensf
* Project  : Final Assignment - Line Sensors Testing
*
* File     : line_sensor.c
*
* Description:
*   This file contains the implementation of the functions for
*   initializing and reading the state of multiple line sensors.
**************************************************************/

#include "line_sensor.h"
#include <stdio.h>
#include <stdlib.h>
#include <pigpio.h>
#include <unistd.h>
#include <time.h>

// Array to store sensor readings
int sensor_readings[MAX_READINGS][3];
int reading_index = 0;

// Initialize the line sensors GPIO pins
void line_sensors_init() {
    if (gpioInitialise() < 0) {
        fprintf(stderr, "pigpio initialization failed\n");
        exit(1);
    }
    gpioSetMode(SENSOR_1_PIN, PI_INPUT);
    gpioSetMode(SENSOR_2_PIN, PI_INPUT);
    gpioSetMode(SENSOR_3_PIN, PI_INPUT);
}

// Read the state of all line sensors and store in an array
void read_line_sensors(int* sensor_states) {
    sensor_states[0] = gpioRead(SENSOR_1_PIN);
    sensor_states[1] = gpioRead(SENSOR_2_PIN);
    sensor_states[2] = gpioRead(SENSOR_3_PIN);
}

// Test the line sensors and store results in an array
void test_line_sensors() {
    time_t start_time = time(NULL);
    time_t current_time;

    while (1) {
        current_time = time(NULL);

        // Check if the program should terminate
        if (difftime(current_time, start_time) >= TIME_DURATION_SECONDS) {
            break;
        }

        // Read the sensor states and store them in the array
        if (reading_index < MAX_READINGS) {
            read_line_sensors(sensor_readings[reading_index]);
            reading_index++;
        }

        // Print the states of the line sensors as 1 or 0
        printf("Reading #%d: %d %d %d\n", reading_index,
               sensor_readings[reading_index - 1][0],
               sensor_readings[reading_index - 1][1],
               sensor_readings[reading_index - 1][2]);

        fflush(stdout);  // Ensure output is displayed immediately
        usleep(50000);   // Sleep for 50ms
    }
}
