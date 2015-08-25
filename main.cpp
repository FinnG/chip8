

#include <iostream>
#include <array>
#include <cstdint>

#include "ram.hpp"

int main()
{
    Chip8Ram ram;
    std::cout << "Ram[0x123] = " << static_cast<int16_t>(ram[0x123]) << std::endl;
    
    
    return 0;
}
