#include <cstdint>

#include "log.h"
#include "mmu.h"
#include "register.h"

// struct InstructionDescription
// {
//   void (CPU::*func)(uint16_t address);
//   uint8_t cycles;
//   uint8_t branch_cycles;
// }

class CPU
{
  public:
    CPU (MMU* mmu);
    int tick();

  private:
    MMU* mmu;

    // std::array<InstructionDescription, 256> table_;
    // std::array<InstructionDescription, 256> cb_table_;

    ByteRegister a, f, b, c, d, e, h, l;

    void set_zero_flag(bool value) { f.write((uint8_t)Flag::Z_ZERO, value); }
    void set_subtract_flag(bool value) { f.write((uint8_t)Flag::N_SUBTRACT, value); }
    void set_halfcarry_flag(bool value) { f.write((uint8_t)Flag::H_HALFCARRY, value); }
    void set_carry_flag(bool value) { f.write((uint8_t)Flag::C_CARRY, value); }

    bool zero_flag() { return f.read((uint8_t)Flag::Z_ZERO); }
    bool subtract_flag() { return f.read((uint8_t)Flag::N_SUBTRACT); }
    bool halfcarry_flag() { return f.read((uint8_t)Flag::H_HALFCARRY); }
    bool carry_flag() { return f.read((uint8_t)Flag::C_CARRY); }

    RegisterPair af = RegisterPair(a, f);
    RegisterPair bc = RegisterPair(b, c);
    RegisterPair de = RegisterPair(d, e);
    RegisterPair hl = RegisterPair(h, l);

    WordRegister sp, pc;

    byte read_pc();
    word read_pc_word();
    int8_t read_pc_signed();

    template<typename R>
    void stack_push(R& reg)
    {
      sp.decrement();
      mmu->write(sp.get(), reg.get() >> 8);
      sp.decrement();
      mmu->write(sp.get(), reg.get() & 0xFF);
    }

    template<typename R>
    void stack_pop(R& reg)
    {
      byte lsb = mmu->read(sp.get());
      sp.increment();
      byte msb = mmu->read(sp.get());
      sp.increment();

      word value = (msb << 8) | lsb;
      reg.set(value);
    }

    void handle_interrupts();

    /**
     * Checks bits 5 - 0
     * Joypad Serial Timer LCD VBlank
     */

    byte InterruptFlag() { return mmu->read(0xFFFF); }
    byte InterruptEnabled() { return mmu->read(0xFF0F); }

    /**
     * Switch on opcode
     */
    int execute(byte opcode, word address);
    int execute_cb(byte opcode, word address);

    /**
     * Halted flag
     */
    bool halted = false;

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

    void opcode_0xAF();
    void opcode_0xAE();
    void opcode_0xAD();
    void opcode_0xAC();
    void opcode_0xAB();
    void opcode_0xAA();
    void opcode_0xA9();
    void opcode_0xA8();
    void opcode_0xEE();

    void opcode_0x87();
    void opcode_0x86();
    void opcode_0x85();
    void opcode_0x84();
    void opcode_0x83();
    void opcode_0x82();
    void opcode_0x81();
    void opcode_0x80();
    void opcode_0xC6();

    void opcode_0x97();
    void opcode_0x96();
    void opcode_0x95();
    void opcode_0x94();
    void opcode_0x93();
    void opcode_0x92();
    void opcode_0x91();
    void opcode_0x90();
    void opcode_0xD6();


    void opcode_0x8F();
    void opcode_0x8D();
    void opcode_0x8C();
    void opcode_0x8B();
    void opcode_0x8A();
    void opcode_0x89();
    void opcode_0x88();

    void opcode_0xCE();
    void opcode_0x8E();


    void opcode_0x9F();
    void opcode_0x9D();
    void opcode_0x9C();
    void opcode_0x9B();
    void opcode_0x9A();
    void opcode_0x99();
    void opcode_0x98();

    void opcode_0xDE();
    void opcode_0x9E();

    void opcode_0x07();
    void opcode_0x17();
    void opcode_0x0F();
    void opcode_0x1F();

    void opcode_0xC0();
    void opcode_0xD0();

    void opcode_0x09();
    void opcode_0x19();
    void opcode_0x29();
    void opcode_0x39();

    void opcode_0xC2();
    void opcode_0xD2();
    void opcode_0xCA();
    void opcode_0xDA();
    void opcode_0xE9();

    void opcode_0x76();

    void opcode_0xD9();

    void opcode_0xF7();
    void opcode_0xE7();
    void opcode_0xD7();
    void opcode_0xC7();

    void opcode_0xFF();
    void opcode_0xEF();
    void opcode_0xDF();
    void opcode_0xCF();

    void opcode_0xE8();

    void opcode_0x27();
    void opcode_0x37();

    void opcode_0x2F();
    void opcode_0x3F();



    /**
     * Opcode implementations
     */
    void Nop();
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

    void JP(bool conditional = true);
    void JP_hl();

    void INC_r8(ByteRegister& reg);

    void JR_cc_e(bool conditional = true);

    void CALL_nn(bool conditional = true);

    void RET_cc(bool conditional = true);
    void RETI();

    void RST(word address);

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

    void XOR(byte value);
    void XOR_r8(ByteRegister& reg);
    void XOR_n8();
    void XOR_r16(RegisterPair& reg);

    void ADD(byte value);
    void ADD_r8(ByteRegister& reg);
    void ADD_n8();
    void ADD_r16(RegisterPair& reg);
    void ADD_hl(word value);
    void ADD_hl_r16(RegisterPair& reg);
    void ADD_hl_r16(WordRegister& reg);
    void ADD_sp_e8();

    void SUB(byte value);
    void SUB_r8(ByteRegister& reg);
    void SUB_n8();
    void SUB_r16(RegisterPair& reg);

    void ADC(byte value);
    void ADC_r8(ByteRegister& reg);
    void ADC_n8();
    void ADC_r16(RegisterPair& reg);

    void SBC(byte value);
    void SBC_r8(ByteRegister& reg);
    void SBC_n8();
    void SBC_r16(RegisterPair& reg);

    void RLCA();
    void RLA();
    void RRCA();
    void RRA();

    void DAA();
    void SCF();
    void CCF();
    void CPL();

    void opcode_cb_0xFF();
    void opcode_cb_0xFE();
    void opcode_cb_0xFD();
    void opcode_cb_0xFC();
    void opcode_cb_0xFB();
    void opcode_cb_0xFA();
    void opcode_cb_0xF9();
    void opcode_cb_0xF8();
    void opcode_cb_0xF7();
    void opcode_cb_0xF6();
    void opcode_cb_0xF5();
    void opcode_cb_0xF4();
    void opcode_cb_0xF3();
    void opcode_cb_0xF2();
    void opcode_cb_0xF1();
    void opcode_cb_0xF0();
    void opcode_cb_0xEF();
    void opcode_cb_0xEE();
    void opcode_cb_0xED();
    void opcode_cb_0xEC();
    void opcode_cb_0xEB();
    void opcode_cb_0xEA();
    void opcode_cb_0xE9();
    void opcode_cb_0xE8();
    void opcode_cb_0xE7();
    void opcode_cb_0xE6();
    void opcode_cb_0xE5();
    void opcode_cb_0xE4();
    void opcode_cb_0xE3();
    void opcode_cb_0xE2();
    void opcode_cb_0xE1();
    void opcode_cb_0xE0();
    void opcode_cb_0xDF();
    void opcode_cb_0xDE();
    void opcode_cb_0xDD();
    void opcode_cb_0xDC();
    void opcode_cb_0xDB();
    void opcode_cb_0xDA();
    void opcode_cb_0xD9();
    void opcode_cb_0xD8();
    void opcode_cb_0xD7();
    void opcode_cb_0xD6();
    void opcode_cb_0xD5();
    void opcode_cb_0xD4();
    void opcode_cb_0xD3();
    void opcode_cb_0xD2();
    void opcode_cb_0xD1();
    void opcode_cb_0xD0();
    void opcode_cb_0xCF();
    void opcode_cb_0xCE();
    void opcode_cb_0xCD();
    void opcode_cb_0xCC();
    void opcode_cb_0xCB();
    void opcode_cb_0xCA();
    void opcode_cb_0xC9();
    void opcode_cb_0xC8();
    void opcode_cb_0xC7();
    void opcode_cb_0xC6();
    void opcode_cb_0xC5();
    void opcode_cb_0xC4();
    void opcode_cb_0xC3();
    void opcode_cb_0xC2();
    void opcode_cb_0xC1();
    void opcode_cb_0xC0();
    void opcode_cb_0xBF();
    void opcode_cb_0xBE();
    void opcode_cb_0xBD();
    void opcode_cb_0xBC();
    void opcode_cb_0xBB();
    void opcode_cb_0xBA();
    void opcode_cb_0xB9();
    void opcode_cb_0xB8();
    void opcode_cb_0xB7();
    void opcode_cb_0xB6();
    void opcode_cb_0xB5();
    void opcode_cb_0xB4();
    void opcode_cb_0xB3();
    void opcode_cb_0xB2();
    void opcode_cb_0xB1();
    void opcode_cb_0xB0();
    void opcode_cb_0xAF();
    void opcode_cb_0xAE();
    void opcode_cb_0xAD();
    void opcode_cb_0xAC();
    void opcode_cb_0xAB();
    void opcode_cb_0xAA();
    void opcode_cb_0xA9();
    void opcode_cb_0xA8();
    void opcode_cb_0xA7();
    void opcode_cb_0xA6();
    void opcode_cb_0xA5();
    void opcode_cb_0xA4();
    void opcode_cb_0xA3();
    void opcode_cb_0xA2();
    void opcode_cb_0xA1();
    void opcode_cb_0xA0();
    void opcode_cb_0x9F();
    void opcode_cb_0x9E();
    void opcode_cb_0x9D();
    void opcode_cb_0x9C();
    void opcode_cb_0x9B();
    void opcode_cb_0x9A();
    void opcode_cb_0x99();
    void opcode_cb_0x98();
    void opcode_cb_0x97();
    void opcode_cb_0x96();
    void opcode_cb_0x95();
    void opcode_cb_0x94();
    void opcode_cb_0x93();
    void opcode_cb_0x92();
    void opcode_cb_0x91();
    void opcode_cb_0x90();
    void opcode_cb_0x8F();
    void opcode_cb_0x8E();
    void opcode_cb_0x8D();
    void opcode_cb_0x8C();
    void opcode_cb_0x8B();
    void opcode_cb_0x8A();
    void opcode_cb_0x89();
    void opcode_cb_0x88();
    void opcode_cb_0x87();
    void opcode_cb_0x86();
    void opcode_cb_0x85();
    void opcode_cb_0x84();
    void opcode_cb_0x83();
    void opcode_cb_0x82();
    void opcode_cb_0x81();
    void opcode_cb_0x80();
    void opcode_cb_0x7F();
    void opcode_cb_0x7E();
    void opcode_cb_0x7D();
    void opcode_cb_0x7C();
    void opcode_cb_0x7B();
    void opcode_cb_0x7A();
    void opcode_cb_0x79();
    void opcode_cb_0x78();
    void opcode_cb_0x77();
    void opcode_cb_0x76();
    void opcode_cb_0x75();
    void opcode_cb_0x74();
    void opcode_cb_0x73();
    void opcode_cb_0x72();
    void opcode_cb_0x71();
    void opcode_cb_0x70();
    void opcode_cb_0x6F();
    void opcode_cb_0x6E();
    void opcode_cb_0x6D();
    void opcode_cb_0x6C();
    void opcode_cb_0x6B();
    void opcode_cb_0x6A();
    void opcode_cb_0x69();
    void opcode_cb_0x68();
    void opcode_cb_0x67();
    void opcode_cb_0x66();
    void opcode_cb_0x65();
    void opcode_cb_0x64();
    void opcode_cb_0x63();
    void opcode_cb_0x62();
    void opcode_cb_0x61();
    void opcode_cb_0x60();
    void opcode_cb_0x5F();
    void opcode_cb_0x5E();
    void opcode_cb_0x5D();
    void opcode_cb_0x5C();
    void opcode_cb_0x5B();
    void opcode_cb_0x5A();
    void opcode_cb_0x59();
    void opcode_cb_0x58();
    void opcode_cb_0x57();
    void opcode_cb_0x56();
    void opcode_cb_0x55();
    void opcode_cb_0x54();
    void opcode_cb_0x53();
    void opcode_cb_0x52();
    void opcode_cb_0x51();
    void opcode_cb_0x50();
    void opcode_cb_0x4F();
    void opcode_cb_0x4E();
    void opcode_cb_0x4D();
    void opcode_cb_0x4C();
    void opcode_cb_0x4B();
    void opcode_cb_0x4A();
    void opcode_cb_0x49();
    void opcode_cb_0x48();
    void opcode_cb_0x47();
    void opcode_cb_0x46();
    void opcode_cb_0x45();
    void opcode_cb_0x44();
    void opcode_cb_0x43();
    void opcode_cb_0x42();
    void opcode_cb_0x41();
    void opcode_cb_0x40();
    void opcode_cb_0x3F();
    void opcode_cb_0x3E();
    void opcode_cb_0x3D();
    void opcode_cb_0x3C();
    void opcode_cb_0x3B();
    void opcode_cb_0x3A();
    void opcode_cb_0x39();
    void opcode_cb_0x38();
    void opcode_cb_0x37();
    void opcode_cb_0x36();
    void opcode_cb_0x35();
    void opcode_cb_0x34();
    void opcode_cb_0x33();
    void opcode_cb_0x32();
    void opcode_cb_0x31();
    void opcode_cb_0x30();
    void opcode_cb_0x2F();
    void opcode_cb_0x2E();
    void opcode_cb_0x2D();
    void opcode_cb_0x2C();
    void opcode_cb_0x2B();
    void opcode_cb_0x2A();
    void opcode_cb_0x29();
    void opcode_cb_0x28();
    void opcode_cb_0x27();
    void opcode_cb_0x26();
    void opcode_cb_0x25();
    void opcode_cb_0x24();
    void opcode_cb_0x23();
    void opcode_cb_0x22();
    void opcode_cb_0x21();
    void opcode_cb_0x20();
    void opcode_cb_0x1F();
    void opcode_cb_0x1E();
    void opcode_cb_0x1D();
    void opcode_cb_0x1C();
    void opcode_cb_0x1B();
    void opcode_cb_0x1A();
    void opcode_cb_0x19();
    void opcode_cb_0x18();
    void opcode_cb_0x17();
    void opcode_cb_0x16();
    void opcode_cb_0x15();
    void opcode_cb_0x14();
    void opcode_cb_0x13();
    void opcode_cb_0x12();
    void opcode_cb_0x11();
    void opcode_cb_0x10();
    void opcode_cb_0x0F();
    void opcode_cb_0x0E();
    void opcode_cb_0x0D();
    void opcode_cb_0x0C();
    void opcode_cb_0x0B();
    void opcode_cb_0x0A();
    void opcode_cb_0x09();
    void opcode_cb_0x08();
    void opcode_cb_0x07();
    void opcode_cb_0x06();
    void opcode_cb_0x05();
    void opcode_cb_0x04();
    void opcode_cb_0x03();
    void opcode_cb_0x02();
    void opcode_cb_0x01();
    void opcode_cb_0x00();


    byte RLC(byte value);
    void RLC_r8(ByteRegister& reg);
    void RLC_hl();

    byte RRC(byte value);
    void RRC_r8(ByteRegister& reg);
    void RRC_hl();

    byte RL(byte value);
    void RL_r8(ByteRegister& reg);
    void RL_hl();

    byte RR(byte value);
    void RR_r8(ByteRegister& reg);
    void RR_hl();

    byte SLA(byte value);
    void SLA_r8(ByteRegister& reg);
    void SLA_hl();

    byte SRA(byte value);
    void SRA_r8(ByteRegister& reg);
    void SRA_hl();

    byte SWAP(byte value);
    void SWAP_r8(ByteRegister& reg);
    void SWAP_hl();

    byte SRL(byte value);
    void SRL_r8(ByteRegister& reg);
    void SRL_hl();

    void BIT(byte value, uint8_t bit);
    void BIT_r8(ByteRegister& reg, uint8_t bit);
    void BIT_hl(uint8_t bit);

    byte RES(byte value, uint8_t bit);
    void RES_r8(ByteRegister& reg, uint8_t bit);
    void RES_hl(uint8_t bit);

    byte SET(byte value, uint8_t bit);
    void SET_r8(ByteRegister& reg, uint8_t bit);
    void SET_hl(uint8_t bit);

};
