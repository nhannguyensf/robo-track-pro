#include "motor/motor_control.h"
#include <stdio.h>
#include <unistd.h>

int main() {
    // Initialize the motor driver
    motor_init();

    // Control the left and right motors
    printf("Both motors moving forward at 75%% speed...\n");
    motor_control(LEFT_MOTOR, 75);   // Left motor forward
    motor_control(RIGHT_MOTOR, 75);  // Right motor forward
    sleep(3);

    // Stop the motors
    printf("Stopping both motors...\n");
    motor_stop(LEFT_MOTOR);
    motor_stop(RIGHT_MOTOR);
    sleep(1);

    // Clean up
    DEV_ModuleExit();
    return 0;
}
