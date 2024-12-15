# File: Top-Level Makefile for Final Assignment - Motor Control, Line Sensor, and PID Controller
#
# Description: This Makefile handles the compilation and execution of
# the main program, motor test, line sensor test, and integrates the PID module.
#
# Commands:
#   make                   - Compiles all programs.
#   make run               - Runs the main program (main.out).
#   make run_test_motor    - Runs the motor test program (test_motor.out).
#   make run_test_line_sensor - Runs the line sensor test program (test_line_sensor.out).
#   make clean             - Cleans up all build artifacts.
#

# Compiler and flags
CC = gcc
CFLAGS = -g -Wall -I./motor -I./line-sensor -I./pid -D USE_BCM2835_LIB
LDFLAGS = -L/usr/local/lib
LIBS = -lbcm2835 -lpthread -lm

# Executable names
MAIN_EXEC = main.out
TEST_MOTOR_EXEC = test_motor.out
TEST_LINE_SENSOR_EXEC = test_line_sensor.out

# Object files for the main program
MAIN_OBJ = main.o motor/motor_control.o motor/PCA9685.o motor/DEV_Config.o pid/pid.o line-sensor/line_sensor.o

# Object files for the motor test program
TEST_MOTOR_OBJ = motor/test_motor.o motor/motor_control.o motor/PCA9685.o motor/DEV_Config.o

# Object files for the line sensor test program
TEST_LINE_SENSOR_OBJ = line-sensor/test_line_sensor.o line-sensor/line_sensor.o

# Default target: Build everything
all: $(MAIN_EXEC) $(TEST_MOTOR_EXEC) $(TEST_LINE_SENSOR_EXEC)

# Compile the main program
$(MAIN_EXEC): $(MAIN_OBJ)
	$(CC) -o $(MAIN_EXEC) $(MAIN_OBJ) $(LDFLAGS) $(LIBS)

# Compile the motor test program
$(TEST_MOTOR_EXEC): $(TEST_MOTOR_OBJ)
	$(CC) -o $(TEST_MOTOR_EXEC) $(TEST_MOTOR_OBJ) $(LDFLAGS) $(LIBS)

# Compile the line sensor test program
$(TEST_LINE_SENSOR_EXEC): $(TEST_LINE_SENSOR_OBJ)
	$(CC) -o $(TEST_LINE_SENSOR_EXEC) $(TEST_LINE_SENSOR_OBJ) $(LDFLAGS) $(LIBS)

# Object file for main
main.o: main.c motor/motor_control.h motor/PCA9685.h motor/DEV_Config.h pid/pid.h line-sensor/line_sensor.h
	$(CC) -c main.c $(CFLAGS) -o main.o

# Object file for PID controller
pid/pid.o: pid/pid.c pid/pid.h
	$(CC) -c pid/pid.c $(CFLAGS) -o pid/pid.o

# Object file for motor_control
motor/motor_control.o: motor/motor_control.c motor/motor_control.h motor/PCA9685.h motor/DEV_Config.h
	$(CC) -c motor/motor_control.c $(CFLAGS) -o motor/motor_control.o

# Object file for PCA9685
motor/PCA9685.o: motor/PCA9685.c motor/PCA9685.h
	$(CC) -c motor/PCA9685.c $(CFLAGS) -o motor/PCA9685.o

# Object file for DEV_Config
motor/DEV_Config.o: motor/DEV_Config.c motor/DEV_Config.h
	$(CC) -c motor/DEV_Config.c $(CFLAGS) -o motor/DEV_Config.o

# Object file for line_sensor
line-sensor/line_sensor.o: line-sensor/line_sensor.c line-sensor/line_sensor.h
	$(CC) -c line-sensor/line_sensor.c $(CFLAGS) -o line-sensor/line_sensor.o

# Object file for test_line_sensor
line-sensor/test_line_sensor.o: line-sensor/test_line_sensor.c line-sensor/line_sensor.h
	$(CC) -c line-sensor/test_line_sensor.c $(CFLAGS) -o line-sensor/test_line_sensor.o

# Object file for test_motor
motor/test_motor.o: motor/test_motor.c motor/motor_control.h motor/PCA9685.h motor/DEV_Config.h
	$(CC) -c motor/test_motor.c $(CFLAGS) -o motor/test_motor.o

# Run the main program
run: $(MAIN_EXEC)
	sudo ./$(MAIN_EXEC)

# Run the motor test program
run_test_motor: $(TEST_MOTOR_EXEC)
	sudo ./$(TEST_MOTOR_EXEC)

# Run the line sensor test program
run_test_line_sensor: $(TEST_LINE_SENSOR_EXEC)
	sudo ./$(TEST_LINE_SENSOR_EXEC)

# Clean all build artifacts
clean:
	rm -f $(MAIN_OBJ) $(TEST_MOTOR_OBJ) $(TEST_LINE_SENSOR_OBJ) pid/pid.o line-sensor/line_sensor.o $(MAIN_EXEC) $(TEST_MOTOR_EXEC) $(TEST_LINE_SENSOR_EXEC)
