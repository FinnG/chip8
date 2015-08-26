#include <array>

#include <SFML/Window.hpp>

struct Registers
{
    std::array<uint8_t, 16> V;
    int16_t I;
    int8_t delay;
    int8_t sound;

    int16_t pc;
    int8_t sp;
};

struct Opcode
{
    union {
        struct  {
            union  {
                struct {
                    uint8_t n4 : 4;
                    uint8_t n3 : 4;
                };
                uint8_t n34;
            };
            uint8_t n2 : 4;
        };
        struct {
            uint16_t n234 : 12;
            uint8_t n1 : 4;
        };
        uint16_t n1234;
    };
};

class Chip8Ram;
class Chip8Display;

class Chip8CPU
{
public:
    Chip8CPU(Chip8Ram& ram, Chip8Display& display);
    void execute(struct Opcode opcode);
    bool is_blocked();
    
private:
    struct Registers regs;
    Chip8Ram& ram;
    Chip8Display& display;
    uint8_t blocked_on;
    bool blocked;
    
    void unknown_opcode(struct Opcode opcode);
    void n1_is_0(struct Opcode opcode);
    void n1_is_1(struct Opcode opcode);
    void n1_is_2(struct Opcode opcode);
    void n1_is_3(struct Opcode opcode);
    void n1_is_4(struct Opcode opcode);
    void n1_is_5(struct Opcode opcode);
    void n1_is_6(struct Opcode opcode);
    void n1_is_7(struct Opcode opcode);
    void n1_is_8(struct Opcode opcode);
    void n1_is_9(struct Opcode opcode);
    void n1_is_A(struct Opcode opcode);
    void n1_is_B(struct Opcode opcode);
    void n1_is_C(struct Opcode opcode);
    void n1_is_D(struct Opcode opcode);
    void n1_is_E(struct Opcode opcode);
    void n1_is_F(struct Opcode opcode);

    void block_until_input(sf::Keyboard::Key key);
    sf::Keyboard::Key char_to_key(uint8_t c);

};
