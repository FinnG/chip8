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

    void load_ram(const std::string& filename);

private:
    static const int ram_size = 4096;
    std::array<int8_t, ram_size> ram;
};

#endif
