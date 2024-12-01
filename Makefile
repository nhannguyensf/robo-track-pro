# File: Top-Level Makefile for Final Assignment - Motor Control
#
# Description: This Makefile handles both the main program and motor testing.
# It consolidates all tasks from the motor folder into this single Makefile.
#
# Commands:
#   make               - Compiles both main.out and test_motor.out.
#   make run           - Runs the main program (main.out).
#   make run_test_motor - Runs the motor test program (test_motor.out).
#   make clean         - Cleans up all build artifacts.
#

# Compiler and flags
CC=gcc
CFLAGS=-g -I./motor -D USE_BCM2835_LIB
LDFLAGS=-L/usr/local/lib
LIBS=-lbcm2835 -lpthread -lm

# Executable names
MAIN_EXEC=main.out
TEST_EXEC=test_motor.out

# Object files for the main program
MAIN_OBJ=main.o motor/motor_control.o motor/PCA9685.o motor/DEV_Config.o

# Object files for the motor test program
TEST_OBJ=motor/test_motor.o motor/motor_control.o motor/PCA9685.o motor/DEV_Config.o

# Default target: Build everything
all: $(MAIN_EXEC) $(TEST_EXEC)

# Compile the main program
$(MAIN_EXEC): $(MAIN_OBJ)
	$(CC) -o $(MAIN_EXEC) $(MAIN_OBJ) $(LDFLAGS) $(LIBS)

# Compile the motor test program
$(TEST_EXEC): $(TEST_OBJ)
	$(CC) -o $(TEST_EXEC) $(TEST_OBJ) $(LDFLAGS) $(LIBS)

# Object file for main
main.o: main.c motor/motor_control.h motor/PCA9685.h motor/DEV_Config.h
	$(CC) -c main.c $(CFLAGS)

# Object file for test_motor
motor/test_motor.o: motor/test_motor.c motor/motor_control.h motor/PCA9685.h motor/DEV_Config.h
	$(CC) -c motor/test_motor.c $(CFLAGS) -o motor/test_motor.o

# Object file for motor_control
motor/motor_control.o: motor/motor_control.c motor/motor_control.h motor/PCA9685.h motor/DEV_Config.h
	$(CC) -c motor/motor_control.c $(CFLAGS) -o motor/motor_control.o

# Object file for PCA9685
motor/PCA9685.o: motor/PCA9685.c motor/PCA9685.h
	$(CC) -c motor/PCA9685.c $(CFLAGS) -o motor/PCA9685.o

# Object file for DEV_Config
motor/DEV_Config.o: motor/DEV_Config.c motor/DEV_Config.h
	$(CC) -c motor/DEV_Config.c $(CFLAGS) -o motor/DEV_Config.o

# Run the main program
run: $(MAIN_EXEC)
	sudo ./$(MAIN_EXEC)

# Run the motor test program
run_test_motor: $(TEST_EXEC)
	sudo ./$(TEST_EXEC)

# Clean all build artifacts
clean:
	rm -f $(MAIN_OBJ) $(TEST_OBJ) $(MAIN_EXEC) $(TEST_EXEC)
