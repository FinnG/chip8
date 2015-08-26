#include <iostream>
#include <fstream>

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
    uint16_t most = ram[addr];
    LOG(INFO) << "most 0x" << std::hex << most;
        uint16_t least = 0x00FF & ram[addr + 1];
        LOG(INFO) << "least 0x" << std::hex << least;
    uint16_t result = (most << 8) | least;
    LOG(INFO) << "result 0x" << std::hex << result;
    return result;
}

void Chip8Ram::write_instruction(uint16_t addr, uint16_t instr)
{
    uint16_t* ptr = (uint16_t*)&ram[addr];
    *ptr = instr;
}

void Chip8Ram::load_ram(const std::string& filename)
{
    LOG(INFO) << "Loading " << filename;
    std::ifstream file(filename, std::ios::in | std::ios::binary);
    file.read((char*)&ram[0x200], ram_size - 0x200);
    LOG(INFO) << "ram[0]=0x" << std::hex << (uint16_t)ram[0];
    LOG(INFO) << "ram[0x200]=0x" << std::hex << (uint16_t)ram[0x201];
    file.close();
}