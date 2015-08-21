

SOURCES=cpu.cpp main.cpp

default: all

all: 
	g++ -g -std=gnu++11 -o chip8 $(SOURCES)
