SOURCES=ram.cpp display.cpp cpu.cpp main.cpp
LIBS=-lsfml-graphics -lsfml-window -lsfml-system

BINARY=chip8
OBJECTS=$(SOURCES:.cpp=.o)
CC=g++

default: all

all: $(OBJECTS)
	$(CC) -o $(BINARY) $(OBJECTS) $(LIBS)

%.o: %.cpp
	$(CC) -c -g -std=gnu++11 -o $@ $<

clean:
	rm -f $(OBJECTS)
	rm -f $(BINARY)
