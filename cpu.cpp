/* http://devernay.free.fr/hacks/chip8/C8TECH10.HTM */

#include <functional>
#include <iostream>
#include <cassert>
#include <random>
#include <thread>
#include <ctime>

#include "cpu.hpp"
#include "ram.hpp"
#include "display.hpp"
#include "log.hpp"


#define V0 regs.V[0x0]
#define V1 regs.V[0x1]
#define V2 regs.V[0x2]
#define V3 regs.V[0x3]
#define V4 regs.V[0x4]
#define V5 regs.V[0x5]
#define V6 regs.V[0x6]
#define V7 regs.V[0x7]
#define V8 regs.V[0x8]
#define V9 regs.V[0x9]
#define VA regs.V[0xA]
#define VB regs.V[0xB]
#define VC regs.V[0xC]
#define VD regs.V[0xD]
#define VE regs.V[0xE]
#define VF regs.V[0xF]
#define PC regs.pc
#define SP regs.sp
#define I  regs.I

Chip8CPU::Chip8CPU(Chip8Ram& ram, Chip8Display& display)
    : ram(ram), display(display), blocked(false)
{
    for(int8_t reg : regs.V)
        reg = 0;

    PC = 0x200;
    SP = 0;
}

void Chip8CPU::execute(struct Opcode opcode)
{
    using std::placeholders::_1;
    std::array<std::function<void(struct Opcode)>, 16> n1_funcs = {
        std::bind(&Chip8CPU::n1_is_0, this, _1),
        std::bind(&Chip8CPU::n1_is_1, this, _1),
        std::bind(&Chip8CPU::n1_is_2, this, _1),
        std::bind(&Chip8CPU::n1_is_3, this, _1),
        std::bind(&Chip8CPU::n1_is_4, this, _1),
        std::bind(&Chip8CPU::n1_is_5, this, _1),
        std::bind(&Chip8CPU::n1_is_6, this, _1),
        std::bind(&Chip8CPU::n1_is_7, this, _1),
        std::bind(&Chip8CPU::n1_is_8, this, _1),
        std::bind(&Chip8CPU::n1_is_9, this, _1),
        std::bind(&Chip8CPU::n1_is_A, this, _1),
        std::bind(&Chip8CPU::n1_is_B, this, _1),
        std::bind(&Chip8CPU::n1_is_C, this, _1),
        std::bind(&Chip8CPU::n1_is_D, this, _1),
        std::bind(&Chip8CPU::n1_is_E, this, _1),
        std::bind(&Chip8CPU::n1_is_F, this, _1),
    };

    if(opcode.n1 > 0xF)
        unknown_opcode(opcode);
    
    return n1_funcs[opcode.n1](opcode);
}

void Chip8CPU::n1_is_0(struct Opcode opcode)
{
    switch(opcode.n1234) {
    case 0x0000: /* NOP - NOT DEFINED IN SPEC! */
        exit(0);
        break;
    case 0x00E0: /* CLS */
        display.clear();
        PC += 2;
        break;
    case 0x00EE: /* RET */
        PC = ram.read_instruction(SP);
        SP -= 2;
        break;
    default:
        unknown_opcode(opcode);
        break;
    }    
}

void Chip8CPU::n1_is_1(struct Opcode opcode)
{
    assert(opcode.n1 == 1);

    /* 1nnn = JMP addr */
    PC = opcode.n234;
}

void Chip8CPU::n1_is_2(struct Opcode opcode)
{
    assert(opcode.n1 == 2);

    /* 2nnn = CALL addr */
    SP += 2;
    ram.write_instruction(PC, SP);
    PC = opcode.n234;
}

void Chip8CPU::n1_is_3(struct Opcode opcode)
{
    assert(opcode.n1 == 3);

    /* 3xkk = SE Vx, byte */
    if(regs.V[opcode.n2] == opcode.n34) {
        ;
        return;
    }

    PC += 2;
}

void Chip8CPU::n1_is_4(struct Opcode opcode)
{
    assert(opcode.n1 == 4);

    /* 4xkk = SNE Vx, byte */
    if(regs.V[opcode.n2] != opcode.n34) {
       PC += 4;
       return;
    }

    PC += 2;
}

void Chip8CPU::n1_is_5(struct Opcode opcode)
{
    assert(opcode.n2 == 5);
    assert(opcode.n4 == 0);

    /* 5xy0 = SE Vx, Vy */
    if(regs.V[opcode.n2] == regs.V[opcode.n3]) {
        PC += 4;
    }

    PC += 2;
}

void Chip8CPU::n1_is_6(struct Opcode opcode)
{
    assert(opcode.n1 == 6);

    /* 6xkk = LD Vx, byte */
    regs.V[opcode.n2] = opcode.n34;
    PC += 2;
}

void Chip8CPU::n1_is_7(struct Opcode opcode)
{
    assert(opcode.n1 == 7);

    /* 7xkk = ADD Vx, byte */
    regs.V[opcode.n2] = regs.V[opcode.n2] + opcode.n34;
    PC += 2;
}

void Chip8CPU::n1_is_8(struct Opcode opcode)
{
    assert(opcode.n1 == 8);

    int16_t result = 0; /* variable used to store result of some opcodes */

    switch(opcode.n4) {
    case 0x0: /* 8xy0 = LD Vx, Vy */
        regs.V[opcode.n2] = regs.V[opcode.n3];
        break;
    case 0x1: /* 8xy1 = OR Vx, Vy */
        regs.V[opcode.n2] = regs.V[opcode.n2] | regs.V[opcode.n3];
        break;
    case 0x2: /* 8xy2 = AND Vx, Vy */
        regs.V[opcode.n2] = regs.V[opcode.n2] & regs.V[opcode.n3];
        break;
    case 0x3: /* 8xy3 = XOR Vx, Vy */
        regs.V[opcode.n2] = regs.V[opcode.n2] ^ regs.V[opcode.n3];
        break;
    case 0x4: /* 8xy4 = ADD Vx, Vy */
        result = regs.V[opcode.n2] + regs.V[opcode.n3];
        VF = 0;
        if(result > 255)
            VF = 1; /* Set carry flag in VF */
        regs.V[opcode.n2] = result;
        break;
    case 0x5: /* 8xy5 = SUB Vx, Vy */
        result = regs.V[opcode.n2] - regs.V[opcode.n3];
        VF = 0;
        if(result > 0)
            VF = 1; /* Set NOT borrow flag in VF */
        regs.V[opcode.n2] = result;
        break;
    case 0x6: /* 8xy6 = SHR Vx {, Vy} */
        VF = 0;
        if(regs.V[opcode.n2] & 0x1)
            VF = 1; /* If we lose the bottom bit, put it in VF */
        regs.V[opcode.n2] /= 2;
        break;
    case 0x7: /* 8xy7 = SUBN Vx, Vy */
        result = regs.V[opcode.n3] - regs.V[opcode.n2];
        VF = 0;
        if(result > 0)
            VF = 1; /* Set NOT borrow flag in VF */
        regs.V[opcode.n2] = result;
        break;
    case 0xE: /* 8xyE = SHL Vx {, Vy} */
        VF = 0;
        if(regs.V[opcode.n2] & 0x80)
            VF = 1; /* If we lose the top bit, put it in VF */
        regs.V[opcode.n2] *= 2;
        break;
    default:
        unknown_opcode(opcode);
        break;        
    }

    PC += 2;
}

void Chip8CPU::n1_is_9(struct Opcode opcode)
{
    assert(opcode.n1 == 0x9);
    assert(opcode.n4 == 0x0);
    
    /* 9xy0 = SNE Vx, Vy */
    if(regs.V[opcode.n2] != regs.V[opcode.n3]) {
        PC += 4;
    }

    PC += 2;
}

void Chip8CPU::n1_is_A(struct Opcode opcode)
{
    assert(opcode.n1 == 0xA);

    /* Annn = LD I, addr */
    I = opcode.n234;
    PC += 2;
}

void Chip8CPU::n1_is_B(struct Opcode opcode)
{
    assert(opcode.n1 == 0xB);

    /* Bnnn = JP V0, addr */
    PC = opcode.n234 + V0;
    PC += 2;
}

void Chip8CPU::n1_is_C(struct Opcode opcode)
{
    assert(opcode.n1 == 0xC);

    /* Cxkk = RND Vx, byte */
    std::mt19937 rng;
    rng.seed(time(NULL));
    std::uniform_int_distribution<int8_t> int_dist;
    regs.V[opcode.n2] = int_dist(rng) & opcode.n34;
    PC += 2;
}

void Chip8CPU::n1_is_D(struct Opcode opcode)
{
    assert(opcode.n1 == 0xD);

    /* Dxyn = DRW Vx, Vy, nibble */
    uint8_t x = regs.V[opcode.n2];
    uint8_t y = regs.V[opcode.n3];
    uint8_t len = opcode.n4;

    display.draw_sprite(&ram[I], len, x, y);

    PC += 2;
}

void Chip8CPU::n1_is_E(struct Opcode opcode)
{
    assert(opcode.n1 == 0xE);

    switch(opcode.n34) {
    case 0x9E: /* Ex9E = SKP Vx */
        if(sf::Keyboard::isKeyPressed(allowed_keys[opcode.n2])) {
            PC += 4;
            return;
        }
        break;
    case 0xA1: /* ExA1 = SKNP Vx */
        if(sf::Keyboard::isKeyPressed(allowed_keys[opcode.n2])) {
            PC += 4;
            return;
        }
        break;
    default:
        unknown_opcode(opcode);
        break;
    }

    PC += 2;
}

void Chip8CPU::n1_is_F(struct Opcode opcode)
{
    assert(opcode.n1 == 0xF);

    switch(opcode.n34) {
    case 0x07: /* Fx07 = LD Vx, DT */
        regs.V[opcode.n2] = regs.delay;
        break;
    case 0x0A: /* Fx0A = LD Vx, K */
        blocked = true;
        reg_to_set = opcode.n2;
        break;
    case 0x15: /* Fx15 = LD DT, Vx */
        regs.delay = regs.V[opcode.n2];
        break;
    case 0x18: /* Fx18 = LD ST, Vx */
        regs.sound = regs.V[opcode.n2];
        break;
    case 0x1E: /* Fx1E = ADD I, Vx */
        I += regs.V[opcode.n2];
        break;
    case 0x29: /* Fx29 = LD F, Vx */
        I = display.hex_location(regs.V[opcode.n2]);
        break;
    case 0x33: { /* Fx33 = LD B, Vx */
        uint8_t number = opcode.n2;
        uint8_t units = number % 10;
        number /= 10;
        uint8_t tens = number % 10;
        number /= 10;
        uint8_t hundreds = number % 10;
        ram[I] = hundreds;
        ram[I + 1] = tens;
        ram[I + 2] = units;
        break;
    }
    case 0x55: { /* Fx55 = LD [I], Vx */
        for(uint8_t i = 0; i <= opcode.n2; i++) {
            ram[I + i] = regs.V[i];
        }
        break;  
    }       
    case 0x65: /* Fx65 = LD Vx, [I] */
        for(uint8_t i = 0; i <= opcode.n2; i++) {
            regs.V[i] = ram[I + i];
        }
        break;         
    default:
        unknown_opcode(opcode);
        break;
    }   

    PC += 2;
}

void Chip8CPU::unknown_opcode(struct Opcode opcode)
{
    std::cerr << "Unknown opcode: 0x" << std::hex << opcode.n1234 << std::endl;
    assert(0);
}

bool Chip8CPU::is_blocked()
{
    if(!blocked)
        return false;

    for(uint8_t i = 0; i < allowed_keys.size(); i++) {
        if(sf::Keyboard::isKeyPressed(allowed_keys[i])) {
            blocked = false;
            regs.V[reg_to_set] = i;
        }
    }
    
    return blocked;
}

struct Opcode Chip8CPU::get_next_instruction()
{
    struct Opcode op;
    op.n1234 = ram.read_instruction(regs.pc);
    LOG(INFO) << "Read instruction: 0x" << std::hex << op.n1234
        << " from addr: 0x" << regs.pc;
    return op;
}

void Chip8CPU::update_timers()
{
    sf::Time time = clock.restart();
    uint32_t ms = time.asMilliseconds();
    ms_since_last_tick += ms;

    while(ms_since_last_tick >= 16) {
        if(regs.delay != 0)
            regs.delay -= 1;
        if(regs.sound != 0)
            regs.sound -= 1;
        ms_since_last_tick -= 16;
    }
}

