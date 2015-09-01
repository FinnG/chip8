#ifndef DISPLAY_HPP
#define DISPLAY_HPP

#include <array>
#include <iostream>

#include <SFML/Graphics.hpp>

class Chip8Ram;

class Chip8Display
{
public:
    Chip8Display(Chip8Ram& ram, uint32_t screen_width, uint32_t screen_height);
    void clear();
    void draw(sf::RenderWindow& window);
    void draw_sprite(int8_t* sprite_start, uint8_t len, uint8_t x, uint8_t y);
    int16_t hex_location(int8_t hex_char);
    bool needs_update();

private:
    static const int8_t width = 64;
    static const int8_t height = 32;
    uint32_t screen_width = 800;
    uint32_t screen_height = 600;

    bool up_to_date;

    Chip8Ram& ram;
    std::array<std::array<bool, height>, width> pixel_is_set;
    std::array<std::array<sf::RectangleShape, height>, width> pixels;
    std::array<int16_t, 16> hex_locations;
    const std::array<std::array<uint8_t, 5>, 16> hex_charset = {{
            {{0xF0, 0x90, 0x90, 0x90, 0xF0}}, /* 0 */
            {{0x20, 0x60, 0x20, 0x20, 0x70}}, /* 1 */
            {{0xF0, 0x10, 0xF0, 0x80, 0xF0}}, /* 2 */
            {{0xF0, 0x10, 0xF0, 0x10, 0xF0}}, /* 3 */
            {{0x90, 0x90, 0xF0, 0x10, 0x10}}, /* 4 */
            {{0xF0, 0x80, 0xF0, 0x10, 0xF0}}, /* 5 */
            {{0xF0, 0x80, 0xF0, 0x90, 0xF0}}, /* 6 */
            {{0xF0, 0x10, 0x20, 0x40, 0x40}}, /* 7 */
            {{0xF0, 0x90, 0xF0, 0x90, 0xF0}}, /* 8 */
            {{0xF0, 0x90, 0xF0, 0x10, 0xF0}}, /* 9 */
            {{0xF0, 0x90, 0xF0, 0x90, 0x90}}, /* A */
            {{0xE0, 0x90, 0xE0, 0x90, 0xE0}}, /* B */
            {{0xF0, 0x80, 0x80, 0x80, 0xF0}}, /* C */
            {{0xE0, 0x90, 0x90, 0x90, 0xE0}}, /* D */
            {{0xF0, 0x80, 0xF0, 0x80, 0xF0}}, /* E */
            {{0xF0, 0x80, 0xF0, 0x80, 0x80}}, /* F */
        }};
};

#endif
