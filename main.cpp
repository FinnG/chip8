

#include <iostream>
#include <array>
#include <cstdint>

#include "log.hpp"

class Chip8Ram
{
public:
    Chip8Ram()
    {
        /* Init the ram by zeroing out all the memory */
        std::cout << "Initing ram" << std::endl;
        for(int8_t byte : ram) {
            byte = 0;
        }
    }

    int8_t& operator[](std::size_t i)
    {
        std::cout << "Accessing ram at addr " << i << std::endl;
        return ram[i];
    };

    const int8_t& operator[](std::size_t i) const
    {
        std::cout << "Accessing ram 2 at addr " << i << std::endl;
        return ram[i];
    };
    
private:
    static const int RAM_SIZE = 4096;
    std::array<int8_t, RAM_SIZE> ram;
};


int main()
{
    Log log;
    Chip8Ram ram;

    log << "Hello world";
    std::cout << "Ram[0x123] = " << static_cast<int16_t>(ram[0x123]) << std::endl;
    
    
    return 0;
}
