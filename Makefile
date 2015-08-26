

SOURCES=ram.cpp display.cpp cpu.cpp main.cpp
LIBS=-lsfml-graphics -lsfml-window -lsfml-system

default: all

all: 
	g++ -g -std=gnu++11 -o chip8 $(SOURCES) $(LIBS)
