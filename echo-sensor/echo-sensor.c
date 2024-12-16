#include "echo-sensor.h"
#include <bcm2835.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <time.h>  // Required for clock_gettime and CLOCK_REALTIME

// Array to store sensor readings
float echo_distances[NUM_ECHO_SENSORS];

// Initialize GPIO pins for ultrasonic sensors
void echo_sensors_init() {
    if (!bcm2835_init()) {
        fprintf(stderr, "bcm2835 initialization failed\n");
        exit(1);
    }

    // Set Trigger pins as output and Echo pins as input
    bcm2835_gpio_fsel(TRIG_0_PIN, BCM2835_GPIO_FSEL_OUTP);
    bcm2835_gpio_fsel(ECHO_0_PIN, BCM2835_GPIO_FSEL_INPT);
    bcm2835_gpio_fsel(TRIG_1_PIN, BCM2835_GPIO_FSEL_OUTP);
    bcm2835_gpio_fsel(ECHO_1_PIN, BCM2835_GPIO_FSEL_INPT);
    bcm2835_gpio_fsel(TRIG_2_PIN, BCM2835_GPIO_FSEL_OUTP);
    bcm2835_gpio_fsel(ECHO_2_PIN, BCM2835_GPIO_FSEL_INPT);
    bcm2835_gpio_fsel(TRIG_3_PIN, BCM2835_GPIO_FSEL_OUTP);
    bcm2835_gpio_fsel(ECHO_3_PIN, BCM2835_GPIO_FSEL_INPT);
    bcm2835_gpio_fsel(TRIG_4_PIN, BCM2835_GPIO_FSEL_OUTP);
    bcm2835_gpio_fsel(ECHO_4_PIN, BCM2835_GPIO_FSEL_INPT);

    // Ensure Trigger pins are low initially
    bcm2835_gpio_write(TRIG_0_PIN, LOW);
    bcm2835_gpio_write(TRIG_1_PIN, LOW);
    bcm2835_gpio_write(TRIG_2_PIN, LOW);
    bcm2835_gpio_write(TRIG_3_PIN, LOW);
    bcm2835_gpio_write(TRIG_4_PIN, LOW);
    usleep(200000); // Wait 200ms for sensors to stabilize
}

// Function to calculate distance for a single sensor
float calculate_distance(int trig_pin, int echo_pin) {
    struct timespec start, end;
    long start_time, end_time;
    float distance;

    // Trigger the ultrasonic pulse
    bcm2835_gpio_write(trig_pin, HIGH);
    usleep(10);  // 10 microsecond pulse
    bcm2835_gpio_write(trig_pin, LOW);

    // Wait for Echo pin to go high
    while (bcm2835_gpio_lev(echo_pin) == LOW);

    clock_gettime(CLOCK_REALTIME, &start);

    // Wait for Echo pin to go low
    while (bcm2835_gpio_lev(echo_pin) == HIGH);

    clock_gettime(CLOCK_REALTIME, &end);

    // Calculate distance in cm
    start_time = start.tv_sec * 1000000 + start.tv_nsec / 1000;
    end_time = end.tv_sec * 1000000 + end.tv_nsec / 1000;
    long travel_time = end_time - start_time;

    distance = (travel_time / 2.0) * 0.0343;
    return distance;
}

// Read distances from all ultrasonic sensors
void read_echo_sensors(float* sensor_distances) {
    sensor_distances[0] = calculate_distance(TRIG_0_PIN, ECHO_0_PIN);
    sensor_distances[1] = calculate_distance(TRIG_1_PIN, ECHO_1_PIN);
    sensor_distances[2] = calculate_distance(TRIG_2_PIN, ECHO_2_PIN);
    sensor_distances[3] = calculate_distance(TRIG_3_PIN, ECHO_3_PIN);
    sensor_distances[4] = calculate_distance(TRIG_4_PIN, ECHO_4_PIN);
}

// Test the ultrasonic sensors and print their readings
void test_echo_sensors() {
    while (1) {
        read_echo_sensors(echo_distances);
        printf("Distances (cm): ");
        for (int i = 0; i < NUM_ECHO_SENSORS; i++) {
            printf("%.2f ", echo_distances[i]);
        }
        printf("\n");
        fflush(stdout);
        sleep(1); // Delay between readings
    }
}
