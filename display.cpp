#include "display.hpp"
#include "ram.hpp"

#include <cassert>
#include <cstring>

Chip8Display::Chip8Display(Chip8Ram& ram, uint32_t screen_width, uint32_t screen_height)
    : ram(ram), screen_width(screen_width), screen_height(screen_height), up_to_date(false)
{
    clear();

    /* Initialise all rects to right size and position */
    uint32_t rect_width = screen_width / width;
    uint32_t rect_height = screen_height / height;
    for(uint8_t y = 0; y < height; y++) {
        for(uint8_t x = 0; x < width; x++) {
            pixels[x][y].setPosition(x * rect_width, y * rect_height);
            pixels[x][y].setSize(sf::Vector2f(rect_width, rect_height));
        }
    }

    /* Copy the hex charset into the correct area of memory */
    for(uint8_t i = 0; i < hex_charset.size(); i++) {
        int16_t location = i * hex_charset[i].size() + 0x100;
        std::memcpy((void*)&ram[location], (void*)hex_charset[i].data(),
                    hex_charset[i].size());
        hex_locations[i] = location;
    }
}

void Chip8Display::clear()
{
    up_to_date = false;
    
    /* Initialise all pixels to blank */
    for(uint8_t y = 0; y < height; y++) {
        for(uint8_t x = 0; x < width; x++) {
            pixel_is_set[x][y] = false;
        }
    }
}

int16_t Chip8Display::hex_location(int8_t hex_char)
{
    assert(hex_char <= 0xF);
    return hex_locations[hex_char] + 0x100;
}

void Chip8Display::draw(sf::RenderWindow& window)
{
    up_to_date = true;
    
    window.clear(sf::Color::Black);
    
    for(uint8_t y = 0; y < height; y++) {
        for(uint8_t x = 0; x < width; x++) {
            if(!pixel_is_set[x][y])
                continue;

            window.draw(pixels[x][y]);
        }
    }

    window.display();
}

void Chip8Display::draw_sprite(int8_t* sprite_start, uint8_t len, uint8_t x, uint8_t y)
{
    up_to_date = false;
    
    for(uint8_t j = 0; j < len; j++) {
        for(uint8_t i = 0; i < 8; i++) {
            uint8_t mask = 0b10000000 >> i;
            bool set = mask & *sprite_start;

            pixel_is_set[(x + i) % width][(y + j) % height] ^= set;
        }

        sprite_start++;
    }
}

bool Chip8Display::needs_update()
{
    return !up_to_date;
}
