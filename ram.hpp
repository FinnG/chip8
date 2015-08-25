#include <array>

class Chip8Ram
{
public:
    Chip8Ram();
    int8_t& operator[](std::size_t i);
    const int8_t& operator[](std::size_t i) const;
    
private:
    static const int RAM_SIZE = 4096;
    std::array<int8_t, RAM_SIZE> ram;
};
