#include "line_sensor.h"
#include <pigpio.h>  // Include pigpio.h for gpioTerminate and other functions
#include <stdio.h>

int main() {
    // Initialize the line sensors
    line_sensors_init();

    // Run the line sensors test
    test_line_sensors();

    // Terminate GPIO safely
    gpioTerminate();
    printf("Program terminated successfully. Stored %d readings.\n", reading_index);
    fflush(stdout);
    return 0;
}
