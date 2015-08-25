#include "display.hpp"

Chip8Display::Chip8Display()
{
    /* Initialise all pixels to blank */
    for(uint8_t y = 0; y < height; y++) {
        for(uint8_t x = 0; x < width; x++) {
            pixels[x][y] = false;
        }
    }
    
    /* TODO: Copy the hex charset into the correct area of memory */
}

void Chip8Display::draw()
{
    initscr();
    for(uint8_t y = 0; y < height; y++) {
        for(uint8_t x = 0; x < width; x++) {
            if(!pixels[x][y])
                continue;

            mvprintw(y, x, "X");
        }
    }
    refresh();
    getch();
    endwin();
}

void Chip8Display::draw_sprite(int8_t* sprite_start, uint8_t len, uint8_t x, uint8_t y)
{
    /* TODO: The spec says sprite drawing must wrap, this just breaks! */

    for(uint8_t j = 0; j < len; j++) {
        for(uint8_t i = 0; i < 8; i++) {
            uint8_t mask = 0b10000000 >> i;
            bool set = mask & *sprite_start;

            pixels[x + i][y + j] ^= set;
        }

        sprite_start++;
    }
}
