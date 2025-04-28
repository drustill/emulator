#include <cstdint>

#include "../logger.h"
#include "register.h"
#include "mmu.h"

class CPU
{
  public:
    CPU (MMU* mmu);
    int tick();

  private:
    MMU* mmu;

    ByteRegister a, f, b, c, d, e, h, l;

    RegisterPair af = RegisterPair(a, f);
    RegisterPair bc = RegisterPair(b, c);
    RegisterPair de = RegisterPair(d, e);
    RegisterPair hl = RegisterPair(h, l);

    WordRegister sp, pc;

    byte read_pc();
    int8_t read_pc_signed();

    template<typename R>
    void stack_push(R& reg)
    {
      sp.decrement();
      mmu->write(sp.get(), reg.get() >> 8);
      sp.decrement();
      mmu->write(sp.get(), reg.get() & 0xFF);

      // LOG("PUSH: 0x%04X", reg.get());
    }

    template<typename R>
    void stack_pop(R& reg)
    {
      byte lsb = mmu->read(sp.get());
      sp.increment();
      byte msb = mmu->read(sp.get());
      sp.increment();

      word value = (msb << 8) | lsb;
      // LOG("POP: 0x%04X", value);
      reg.set(value);
    }

    /**
     * Switch on opcode
     */
    int execute(byte opcode);

    /**
     * Interrupt master enable
     */
    bool ime = false;

    /**
     * True Condition Cycles
     */
    bool cond_cycles = false;

    /**
     * Opcode functions
     */
    void opcode_0x00();
    void opcode_0xF3();
    void opcode_0xFB();

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

    void opcode_0xC4();
    void opcode_0xD4();

    void opcode_0xCC();
    void opcode_0xDC();

    void opcode_0xCD();

    void opcode_0x18();
    void opcode_0x28();
    void opcode_0x38();

    void opcode_0xC8();
    void opcode_0xD8();

    void opcode_0xC9();

    void opcode_0xC1();
    void opcode_0xD1();
    void opcode_0xE1();
    void opcode_0xF1();

    void opcode_0xC5();
    void opcode_0xD5();
    void opcode_0xE5();
    void opcode_0xF5();

    void opcode_0xA0();
    void opcode_0xA1();
    void opcode_0xA2();
    void opcode_0xA3();
    void opcode_0xA4();
    void opcode_0xA5();
    void opcode_0xA6();
    void opcode_0xA7();
    void opcode_0xE6();

    void opcode_0x05();
    void opcode_0x15();
    void opcode_0x25();
    void opcode_0x35();

    void opcode_0x0D();
    void opcode_0x1D();
    void opcode_0x2D();
    void opcode_0x3D();

    void opcode_0x33();
    void opcode_0x23();
    void opcode_0x13();
    void opcode_0x03();

    void opcode_0x3B();
    void opcode_0x2B();
    void opcode_0x1B();
    void opcode_0x0B();

    void opcode_0xB7();
    void opcode_0xB6();
    void opcode_0xB5();
    void opcode_0xB4();
    void opcode_0xB3();
    void opcode_0xB2();
    void opcode_0xB1();
    void opcode_0xB0();
    void opcode_0xF6();

    void opcode_0xBF();
    void opcode_0xBE();
    void opcode_0xBD();
    void opcode_0xBC();
    void opcode_0xBB();
    void opcode_0xBA();
    void opcode_0xB9();
    void opcode_0xB8();
    void opcode_0xFE();

    /**
     * Opcode implementations
     */
    void LD_r8_r8(ByteRegister& reg1, ByteRegister& reg2);
    void LD_r8_r16(ByteRegister& reg, RegisterPair& reg16);
    void LD_r16_r8(RegisterPair& reg16, ByteRegister& reg);

    void LD_r8_n8(ByteRegister& reg);

    void LD_addr16_n8(RegisterPair& reg);

    void LD_nn16_r8(ByteRegister& reg);
    void LD_r8_nn16(ByteRegister& reg);

    void LDH_r8_n8(ByteRegister& reg);
    void LDH_n8_r8(ByteRegister& reg);

    void LD_r16_nn16(WordRegister& reg);
    void LD_nn16_r16(WordRegister& reg);

    void LD_r16_nn16(RegisterPair& reg);
    void LD_nn16_r16(RegisterPair& reg);

    void JP_n16();

    void INC_r8(ByteRegister& reg);

    void JR_cc_e(bool conditional = true);

    void CALL_nn(bool conditional = true);

    void RET_cc(bool conditional = true);

    void AND(byte value);
    void AND_n8();
    void AND_r8(ByteRegister& reg);
    void AND_r16(RegisterPair& reg);

    void AND_r16(WordRegister& reg);

    void DEC_r8(ByteRegister& reg);
    void DEC_hl();

    void INC_r16(WordRegister& reg);
    void DEC_r16(WordRegister& reg);

    void INC_r16(RegisterPair& reg);
    void DEC_r16(RegisterPair& reg);

    void OR(byte value);
    void OR_r8(ByteRegister& reg);
    void OR_n8();
    void OR_r16(RegisterPair& reg);

    void CP(byte value);
    void CP_r8(ByteRegister& reg);
    void CP_n8();
    void CP_r16(RegisterPair& reg);
};
