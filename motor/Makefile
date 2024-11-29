# File: Makefile for CSC-615 Assignment 3 - Motor Control
#
# Description: This Makefile is used to compile the motor control program.
# The program uses the DEV_Config and PCA9685 libraries to interact with 
# the motor driver HAT.
# 
# Variables:
#   ROOTNAME should be set to lastname_firstname_HW (or similar).
#   HW should be set to the assignment number (3, in this case).
#   The output file will be named assignment3.
#
# Commands:
#   make           - Compiles the assignment3 program.
#   make run       - Runs the assignment3 executable.
#   make clean     - Cleans up all object files and the executable.
#

FIRSTNAME=nhan
LASTNAME=nguyen

ROOTNAME=$(LASTNAME)_$(FIRSTNAME)_HW
HW=3

# Compiler and flags
CC=gcc
CFLAGS= -g -I. -D USE_BCM2835_LIB   # Added -D to define USE_BCM2835_LIB
LDFLAGS= -L/usr/local/lib           # Linker flags to search in /usr/local/lib
LIBS= -lbcm2835 -lpthread -lm       # Link BCM2835, Pthreads, and Math library (removed PIGPIO)

# Executable name
EXEC=test_motor

# Object files
OBJ=test_motor.o PCA9685.o DEV_Config.o

# Target to build the executable
all: $(EXEC)

# Compile the program
$(EXEC): $(OBJ)
	$(CC) -o $(EXEC) $(OBJ) $(LDFLAGS) $(LIBS)

# Object file for test_motor
test_motor.o: test_motor.c PCA9685.h DEV_Config.h
	$(CC) -c test_motor.c $(CFLAGS)

# Object file for PCA9685
PCA9685.o: PCA9685.c PCA9685.h
	$(CC) -c PCA9685.c $(CFLAGS)

# Object file for DEV_Config
DEV_Config.o: DEV_Config.c DEV_Config.h
	$(CC) -c DEV_Config.c $(CFLAGS)

# Clean up the directory
clean:
	rm -f $(OBJ) $(EXEC)

# Run the program
run: $(EXEC)
	sudo ./$(EXEC)
