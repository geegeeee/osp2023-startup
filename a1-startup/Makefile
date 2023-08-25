
##
 # startup code provided by Paul Miller for COSC1114 - Operating Systems
 # Principles
 ##

# provide make targets here to build the two programs 

CC = g++
CFLAGS = -std=c++11 -Wall

DIR1 = copier_files
DIR2 = mtcopier_files
SRCS1 = $(DIR1)/main.cpp $(DIR1)/reader.h $(DIR1)/writer.h
SRCS2 = $(DIR2)/main.cpp $(DIR2)/reader.h $(DIR2)/writer.h

.PHONY: all clean

all: copier mtcopier

copier: $(SRCS)
	$(CC) $(CFLAGS) -o $@ $(SRCS1)

mtcopier: $(SRCS)
	$(CC) $(CFLAGS) -o $@ $(SRCS2)
	$(CC) $(CFLAGS) -o $@ $^ -lpthread

clean:
	rm -f copier
