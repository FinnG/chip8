

SOURCES=ram.cpp display.cpp cpu.cpp main.cpp
LIBS=-lncurses

default: all

all: 
	g++ -g -std=gnu++11 -o chip8 $(SOURCES) $(LIBS)
