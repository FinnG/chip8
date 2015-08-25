

#include <iostream>
#include <array>
#include <cstdint>

#include "ram.hpp"
#include "display.hpp"
#include "cpu.hpp"

int main()
{
    Chip8Ram ram;
    Chip8Display display;
    Chip8CPU cpu(ram, display);
    
    std::cout << "Ram[0x123] = " << static_cast<int16_t>(ram[0x123]) << std::endl;
    
    return 0;
}
