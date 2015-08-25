#include <array>
#include <iostream>
#include <ncurses.h>

class Chip8Ram;

class Chip8Display
{
public:
    Chip8Display(Chip8Ram& ram);
    void draw();
    void draw_sprite(int8_t* sprite_start, uint8_t len, uint8_t x, uint8_t y);
    int16_t hex_location(int8_t hex_char);

private:
    static const int8_t width = 64;
    static const int8_t height = 32;

    Chip8Ram& ram;

    std::array<std::array<bool, height>, width> pixels;

    std::array<int16_t, 16> hex_locations;

    /* TODO: this data should be stored in the correct part of the Chip8 mem */
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
