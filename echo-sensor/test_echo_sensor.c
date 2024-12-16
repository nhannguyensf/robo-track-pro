#include "echo_sensor.h"
#include <bcm2835.h>
#include <stdio.h>

int main() {
    // Initialize the ultrasonic sensors
    echo_sensors_init();

    // Run the ultrasonic sensors test
    test_echo_sensors();

    // Terminate GPIO safely
    bcm2835_close();
    printf("Program terminated successfully.\n");
    fflush(stdout);
    return 0;
}
