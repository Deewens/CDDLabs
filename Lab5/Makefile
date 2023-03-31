#Joseph Kehoe 13/9/2017
#Second improved Makefile
#Used to contain commands to compile projects

# Name of the build file
TARGET_EXEC := producerConsumer

CC=g++
CFLAGS= -std=c++11 -pthread

#This rule says that each .o file depends on a .cpp file of the same name
%.o: %.cpp
	$(CC) -c -o $@ $< $(CFLAGS) $(DEBUGFLAGS)

# Link .o(bjects) files, and ask make to compile them if they are in the list
ALL: SafeBuffer.o Semaphore.o main.o 
	$(CC) -o ${TARGET_EXEC} SafeBuffer.o Semaphore.o main.o $(CFLAGS) $(DEBUGFLAGS)

# Debug rule to compile the program to use gdb to debug it
DEBUG: DEBUGFLAGS = -DDEBUG -Wall
DEBUG: ALL

.PHONY: doc CLEAN

doc: 
	rm -rf doc/
	doxygen

#this is customary and just deletes all .o files
CLEAN:
	rm *.o
