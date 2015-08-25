

#include <iostream>
#include <array>
#include <cstdint>

#include "ram.hpp"
#include "display.hpp"
#include "cpu.hpp"

int main()
{
    Chip8Ram ram;
    Chip8Display display(ram);
    Chip8CPU cpu(ram, display);

    struct Opcode op;
    op.n1234 = 0x600F;
    cpu.execute(op);
    op.n1234 = 0xF029;
    cpu.execute(op);
    op.n1234 = 0xD005;
    cpu.execute(op);
    display.draw();
    
    return 0;
}
