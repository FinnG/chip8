#include <iostream>

enum class LogCategory
{
    CHIP8_DECODER,
    CHIP8_ERROR,
    CHIP8_INFO,
    CHIP8_WARNING,
};

class Log
{
public:
    Log() {}
    
    template<typename T>
    Log& operator<<(T t)
    {
        std::cout << t;
        return *this;
    }
};
