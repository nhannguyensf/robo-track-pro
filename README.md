# Motor Control with WaveShare Motor Driver HAT

## Project Overview
This project demonstrates motor control using the **WaveShare Motor Driver HAT** and **PCA9685 PWM Controller** on a Raspberry Pi. The program allows precise control of two motors, including speed, direction, and stopping, through a modular design with a clear separation of implementation, testing, and main control logic.

## Features
- **Motor Initialization**: Sets up the PWM controller and motor driver.
- **Speed and Direction Control**: Adjusts motor speed (0-100%) and direction (forward/reverse).
- **Stopping Motors**: Provides a clean stop mechanism for motors.
- **Testing Framework**: Includes a test program for validating motor operations.

## Folder Structure
project/
├── motor/
│ ├── DEV_Config.c # Raspberry Pi hardware configuration
│ ├── DEV_Config.h # Configuration header
│ ├── PCA9685.c # PCA9685 PWM controller implementation
│ ├── PCA9685.h # PCA9685 header
│ ├── motor_control.c # Motor control implementation
│ ├── motor_control.h # Motor control header
│ ├── test_motor.c # Test program for motor functionality
├── main.c # Main program
├── Makefile # Top-level build file


## Prerequisites
### Hardware
- Raspberry Pi with I2C interface enabled.
- WaveShare Motor Driver HAT.
- Two DC motors connected to the HAT.

### Software
- GCC (GNU Compiler Collection)
- BCM2835 Library
- Linux OS (Debian-based recommended)

## Installation
1. Clone the repository:
   ```bash
   git clone https://github.com/nhannguyensf/motor-control.git
   cd motor-control


Install the BCM2835 library:
sudo apt update
sudo apt install libbcm2835-dev

Enable I2C on the Raspberry Pi:
sudo raspi-config
Navigate to Interfacing Options > I2C and enable it.

Building the Project
Use the provided Makefile to compile the project:

Build all components:
make
Clean build artifacts:
make clean
Running the Programs

Main Program:
Controls the motors with a predefined sequence:
make run

Motor Test Program:
Validates motor functionality:
make run_test_motor

File Descriptions

main.c: The main program demonstrating motor control functionality.
motor_control.c / motor_control.h: Contains the motor control logic, including initialization, speed, and direction control.
test_motor.c: A test program to verify motor operations.
DEV_Config.c / DEV_Config.h: Hardware interface and Raspberry Pi GPIO configuration.
PCA9685.c / PCA9685.h: Interface for the PCA9685 PWM controller.
Usage
Example Workflow

Compile the project:
make
Run the motor test program:
make run_test_motor
Run the main program:
make run
Clean the directory:
make clean
Notes

Ensure the motors are securely connected to the Motor Driver HAT.
Adjust PWM frequency in motor_control.c as needed for your motor specifications.
Contributors

Nhan Nguyen
GitHub: nhannguyensf
License
This project is licensed under the MIT License. See the LICENSE file for details.