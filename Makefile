# File: Top-Level Makefile for Final Assignment - Main Control
#
# Description: This Makefile handles both the main program and motor testing.
# It delegates motor-specific tasks to the motor/Makefile.
#
# Commands:
#   make           - Compiles the main program.
#   make run       - Runs the main program.
#   make run_test_motor - Runs the motor test program.
#   make clean     - Cleans up all build artifacts.
#

# Compiler and flags
CC=gcc
CFLAGS=-g -I./motor -D USE_BCM2835_LIB
LDFLAGS=-L/usr/local/lib
LIBS=-lbcm2835 -lpthread -lm

# Executable name
MAIN_EXEC=final_motor_control

# Object files for the main program
MAIN_OBJ=main.o motor/motor_control.o motor/PCA9685.o motor/DEV_Config.o

# Subdirectory Makefile for motor
MOTOR_DIR=motor
MOTOR_MAKEFILE=$(MOTOR_DIR)/Makefile

# Default target
all: $(MAIN_EXEC)

# Compile the main program
$(MAIN_EXEC): $(MAIN_OBJ)
	$(CC) -o $(MAIN_EXEC) $(MAIN_OBJ) $(LDFLAGS) $(LIBS)

# Object file for main
main.o: main.c motor/motor_control.h motor/PCA9685.h motor/DEV_Config.h
	$(CC) -c main.c $(CFLAGS)

# Delegate to the motor Makefile for testing
run_test_motor:
	$(MAKE) -C $(MOTOR_DIR) run

# Clean all build artifacts
clean:
	rm -f $(MAIN_OBJ) $(MAIN_EXEC)
	$(MAKE) -C $(MOTOR_DIR) clean

# Run the main program
run: $(MAIN_EXEC)
	sudo ./$(MAIN_EXEC)
