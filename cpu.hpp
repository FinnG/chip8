#include <array>

struct Registers
{
    std::array<int8_t, 16> V;
    int16_t I;
    int8_t delay;
    int8_t sound;

    int16_t pc;
    int8_t sp;
};

struct Opcode
{
    union {
        uint16_t n1234;
        struct {
            uint8_t n1 : 4;
            union {
                uint16_t n234 : 12;
                struct {
                    uint8_t n2 : 4;
                    union {
                        uint8_t n34;
                        struct {
                            uint8_t n3 : 4;
                            uint8_t n4 : 4;
                        };
                    };
                };
            };
            
        };
    };
};

class Chip8CPU
{
public:
    Chip8CPU();
    void execute(struct Opcode opcode);
    
private:
    struct Registers regs;
    
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
};