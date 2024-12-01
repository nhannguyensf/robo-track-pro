/**************************************************************
* Class    : CSC-615-01 Fall 2024
* Name     : Nhan Nguyen
* Student ID: 923100929
* Github   : nhannguyensf
* Project  : Final Assignment - Line Sensors Testing
*
* File     : line_sensor.h
*
* Description:
*   This header file contains the constants, function prototypes,
*   and shared variables for testing multiple line sensors.
**************************************************************/

#ifndef LINE_SENSOR_H
#define LINE_SENSOR_H

// GPIO pins for Line Sensors
#define SENSOR_1_PIN 17
#define SENSOR_2_PIN 27
#define SENSOR_3_PIN 22

// Define time duration and array size
#define TIME_DURATION_SECONDS 20
#define MAX_READINGS 400  // Assuming 50ms intervals for 20 seconds

// Array to store sensor readings
extern int sensor_readings[MAX_READINGS][3];
extern int reading_index;

// Function Prototypes
void line_sensors_init();
void read_line_sensors(int* sensor_states);
void test_line_sensors();

#endif // LINE_SENSOR_H
