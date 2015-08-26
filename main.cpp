

#include <iostream>
#include <array>
#include <cstdint>

#include "ram.hpp"
#include "display.hpp"
#include "cpu.hpp"
#include "log.hpp"

int main()
{
    Chip8Ram ram;
    Chip8Display display(ram, 800, 600);
    Chip8CPU cpu(ram, display);

    struct Opcode op;
    op.n1234 = 0x600F;
    cpu.execute(op);
    op.n1234 = 0xF029;
    cpu.execute(op);
    op.n1234 = 0xD005;
    cpu.execute(op);

    sf::RenderWindow window(sf::VideoMode(800, 600), "Chip8");
    while(window.isOpen()) {
        sf::Event event;
        while(window.pollEvent(event)) {
            if(event.type == sf::Event::Closed)
                window.close();
        }

        if(cpu.is_blocked()) {
            continue;
        }
        LOG() << "CPU unblocked, waiting for key 0";
        op.n1234 = 0xF00A;
        cpu.execute(op);

        display.draw(window);
    }
    
    return 0;
}
