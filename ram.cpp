#include <iostream>

#include "ram.hpp"
#include "log.hpp"

Chip8Ram::Chip8Ram()
{
    /* Init the ram by zeroing out all the memory */
    LOG(INFO) << "Start up, clearing memory";
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

uint16_t Chip8Ram::read_instruction(uint16_t addr)
{
	uint16_t* result = (uint16_t*)&ram[addr];
	return *result;
}

void Chip8Ram::write_instruction(uint16_t addr, uint16_t instr)
{
	uint16_t* ptr = (uint16_t*)&ram[addr];
	*ptr = instr;
}
