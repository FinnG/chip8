#include <iostream>

#include "ram.hpp"
#include "log.hpp"

Chip8Ram::Chip8Ram()
{
    /* Init the ram by zeroing out all the memory */
    LOG() << "Start up, clearing memory";
    for(int8_t byte : ram) {
        byte = 0;
    }
}

int8_t& Chip8Ram::operator[](std::size_t i)
{
    return ram[i];
}

const int8_t& Chip8Ram::operator[](std::size_t i) const
{
    return ram[i];
}
