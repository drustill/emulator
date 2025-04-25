#include <cstdint>

#include "../logger.h"
#include "register.h"
#include "mmu.h"

class CPU
{
  public:
    CPU (MMU* mmu, Logger* logger = nullptr);
    int tick();

    int execute(byte opcode);

  private:
    MMU* mmu;
    Flags flags;

    ByteRegister a, b, c, d, e, h, l;
    WordRegister af, bc, de, hl;
    WordRegister sp, pc;

    /**
     * Safe logging
     */
    Logger* logger;
    void log_(const char* msg) { if (logger) logger->log(msg); }

    /**
     * Opcode functions
     */
    void opcode_0x00();

    void opcode_0x01();
    void opcode_0x11();
    void opcode_0x21();
    void opcode_0x31();

    void opcode_0x08();

    void opcode_0x20();
    void opcode_0x30();

    void opcode_0x02();
    void opcode_0x12();
    void opcode_0x22();
    void opcode_0x32();

    void opcode_0x04();
    void opcode_0x14();
    void opcode_0x24();
    void opcode_0x34();

    void opcode_0x06();
    void opcode_0x16();
    void opcode_0x26();
    void opcode_0x36();

    void opcode_0x0A();
    void opcode_0x1A();
    void opcode_0x2A();
    void opcode_0x3A();

    void opcode_0x0C();
    void opcode_0x1C();
    void opcode_0x2C();
    void opcode_0x3C();

    void opcode_0x0E();
    void opcode_0x1E();
    void opcode_0x2E();
    void opcode_0x3E();

    void opcode_0x40();
    void opcode_0x41();
    void opcode_0x42();
    void opcode_0x43();
    void opcode_0x44();
    void opcode_0x45();
    void opcode_0x46();
    void opcode_0x47();

    void opcode_0x48();
    void opcode_0x49();
    void opcode_0x4A();
    void opcode_0x4B();
    void opcode_0x4C();
    void opcode_0x4D();
    void opcode_0x4E();
    void opcode_0x4F();

    void opcode_0x50();
    void opcode_0x51();
    void opcode_0x52();
    void opcode_0x53();
    void opcode_0x54();
    void opcode_0x55();
    void opcode_0x56();
    void opcode_0x57();

    void opcode_0x58();
    void opcode_0x59();
    void opcode_0x5A();
    void opcode_0x5B();
    void opcode_0x5C();
    void opcode_0x5D();
    void opcode_0x5E();
    void opcode_0x5F();

    void opcode_0x60();
    void opcode_0x61();
    void opcode_0x62();
    void opcode_0x63();
    void opcode_0x64();
    void opcode_0x65();
    void opcode_0x66();
    void opcode_0x67();

    void opcode_0x68();
    void opcode_0x69();
    void opcode_0x6A();
    void opcode_0x6B();
    void opcode_0x6C();
    void opcode_0x6D();
    void opcode_0x6E();
    void opcode_0x6F();

    void opcode_0x70();
    void opcode_0x71();
    void opcode_0x72();
    void opcode_0x73();
    void opcode_0x74();
    void opcode_0x75();
    void opcode_0x77();
    void opcode_0x78();
    void opcode_0x79();
    void opcode_0x7A();
    void opcode_0x7B();
    void opcode_0x7C();
    void opcode_0x7D();
    void opcode_0x7E();
    void opcode_0x7F();

    void opcode_0xE2();
    void opcode_0xF2();

    void opcode_0xEA();
    void opcode_0xFA();

    void opcode_0xE0();
    void opcode_0xF0();

    void opcode_0xC3();

    void opcode_0xF8();
    void opcode_0xF9();

    /**
     * Opcode implementations
     */
    void LD_r8_r8(ByteRegister& reg1, ByteRegister& reg2);
    void LD_r8_r16(ByteRegister& reg, WordRegister& reg16);
    void LD_r16_r8(WordRegister& reg16, ByteRegister& reg);

    void LD_r8_n8(ByteRegister& reg);

    void LD_addr16_n8(WordRegister& reg);

    void LD_nn16_r8(ByteRegister& reg);
    void LD_r8_nn16(ByteRegister& reg);

    void LDH_r8_n8(ByteRegister& reg);
    void LDH_n8_r8(ByteRegister& reg);


    void LD_r16_nn16(WordRegister& reg);
    void LD_nn16_r16(WordRegister& reg);

    void JP_n16();

    void INC_r8(ByteRegister& reg);

    void JR_cc_e(bool flag);
};
