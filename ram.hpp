#ifndef RAM_HPP
#define RAM_HPP

#include <array>

class Chip8Ram
{
public:
    Chip8Ram();
    int8_t& operator[](std::size_t i);
    const int8_t& operator[](std::size_t i) const;

    uint16_t read_instruction(uint16_t addr);
    void write_instruction(uint16_t addr, uint16_t instr);
    
private:
    static const int RAM_SIZE = 4096;
    std::array<int8_t, RAM_SIZE> ram;
};

#endif
