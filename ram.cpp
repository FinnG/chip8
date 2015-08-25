#include <iostream>

#include "ram.hpp"

Chip8Ram::Chip8Ram()
{
    /* Init the ram by zeroing out all the memory */
    std::cout << "Initing ram" << std::endl;
    for(int8_t byte : ram) {
        byte = 0;
    }
}

int8_t& Chip8Ram::operator[](std::size_t i)
{
    std::cout << "Accessing ram at addr " << i << std::endl;
    return ram[i];
}

const int8_t& Chip8Ram::operator[](std::size_t i) const
{
    std::cout << "Accessing ram 2 at addr " << i << std::endl;
    return ram[i];
}
