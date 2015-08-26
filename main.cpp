

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

    /* Write a (very simple!) program into ram */
    ram.write_instruction(0x200, 0xF00A); /* Ld char into V0 */
    ram.write_instruction(0x202, 0xF029); /* Find sprite for char in V0 */
    ram.write_instruction(0x204, 0x00E0); /* Clear screen */
    ram.write_instruction(0x206, 0xD005); /* Draw said sprite */
    ram.write_instruction(0x208, 0x1200); /* Jump to 0x200 */

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

        cpu.execute(cpu.get_next_instruction());

        display.draw(window);
    }
    
    return 0;
}
