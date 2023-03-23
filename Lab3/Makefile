#Joseph Kehoe 13/9/2017
#Second improved Makefile
#Used to contain commands to compile projects
#Equivalent(?) to a project file in VStudio -- only better!
#See http://www.cs.colby.edu/maxwell/courses/tutorials/maketutor/ for info.

# Name of the build file
TARGET_EXEC := mutualExclusion

CC=g++
CFLAGS= -std=c++11 -pthread

#This rule says that each .o file depends on a .cpp file of the same name
%.o: %.cpp
	$(CC) -c -o $@ $< $(CFLAGS) $(DEBUGFLAGS)

ALL: Semaphore.o main.o 
	$(CC) -o ${TARGET_EXEC} Semaphore.o main.o $(CFLAGS) $(DEBUGFLAGS)

DEBUG: DEBUGFLAGS = -DDEBUG
DEBUG: ALL

#this is customary and just deletes all .o files
CLEAN:
	rm *.o
