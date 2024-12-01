# File: Makefile for CSC-615 Final Assignment - Motor Control
#
# Description: This Makefile is used to compile the motor control program.
# The program uses the DEV_Config, PCA9685, and motor_control libraries
# to interact with the motor driver HAT.
#
# Variables:
#   ROOTNAME should be set to lastname_firstname_final (or similar).
#   The output file will be named final_motor_control.
#
# Commands:
#   make           - Compiles the final_motor_control program.
#   make run       - Runs the final_motor_control executable.
#   make clean     - Cleans up all object files and the executable.
#

FIRSTNAME=nhan
LASTNAME=nguyen

ROOTNAME=$(LASTNAME)_$(FIRSTNAME)_final

# Compiler and flags
CC=gcc
CFLAGS= -g -I. -D USE_BCM2835_LIB   # Added -D to define USE_BCM2835_LIB
LDFLAGS= -L/usr/local/lib           # Linker flags to search in /usr/local/lib
LIBS= -lbcm2835 -lpthread -lm       # Link BCM2835, Pthreads, and Math library

# Executable name
EXEC=test_motor.out

# Object files
OBJ=test_motor.o motor_control.o PCA9685.o DEV_Config.o

# Target to build the executable
all: $(EXEC)

# Compile the program
$(EXEC): $(OBJ)
	$(CC) -o $(EXEC) $(OBJ) $(LDFLAGS) $(LIBS)

# Object file for test_motor
test_motor.o: test_motor.c motor_control.h PCA9685.h DEV_Config.h
	$(CC) -c test_motor.c $(CFLAGS)

# Object file for motor_control
motor_control.o: motor_control.c motor_control.h PCA9685.h DEV_Config.h
	$(CC) -c motor_control.c $(CFLAGS)

# Object file for PCA9685
PCA9685.o: PCA9685.c PCA9685.h
	$(CC) -c PCA9685.c $(CFLAGS)

# Object file for DEV_Config
DEV_Config.o: DEV_Config.c DEV_Config.h
	$(CC) -c DEV_Config.c $(CFLAGS)

# Clean up the directory
clean:
	rm -f $(OBJ) $(EXEC) *.out

# Run the program
run: $(EXEC)
	sudo ./$(EXEC)
