/**************************************************************
* Class    : CSC-615-01 Fall 2024
* Name     : Nhan Nguyen
* Student ID: 923100929
* Github   : nhannguyensf
* Project  : Ultrasonic Sensors for Obstacle Detection
*
* File     : echo-sensor.h
*
* Description:
*   This header file contains constants, function prototypes,
*   and shared variables for managing 5 ultrasonic echo sensors.
**************************************************************/

#ifndef ECHO_SENSOR_H
#define ECHO_SENSOR_H

// GPIO pins for ultrasonic sensors
#define TRIG_0_PIN 4
#define ECHO_0_PIN 5
#define TRIG_1_PIN 6
#define ECHO_1_PIN 13
#define TRIG_2_PIN 26
#define ECHO_2_PIN 12
#define TRIG_3_PIN 20
#define ECHO_3_PIN 21
#define TRIG_4_PIN 25
#define ECHO_4_PIN 16

// Define total number of sensors
#define NUM_ECHO_SENSORS 5

// Array to store sensor readings in centimeters
extern float echo_distances[NUM_ECHO_SENSORS];

// Function Prototypes
void echo_sensors_init();                      // Initialize GPIO pins for ultrasonic sensors
void read_echo_sensors(float* sensor_distances); // Read the distances from all sensors
void test_echo_sensors();                      // Test the ultrasonic sensors and log data

#endif // ECHO_SENSOR_H
