#include "cpu.h"
#include "../logger.h"

/**
 * r8: ByteRegister
 * r16: WordRegister or RegisterPair
 * n8: 8-bit immediate value
 * nn16: 16-bit immediate value
 */

/* MISC */
void CPU::opcode_0x00() { /* NOP */ }
void CPU::opcode_0xF3() { ime = false; }
void CPU::opcode_0xFB() { ime = true; }
void CPU::opcode_0x76() { halted = true; }

void CPU::opcode_0x07() { RLCA(); }
void CPU::opcode_0x17() { RLA(); }
void CPU::opcode_0x0F() { RRCA(); }
void CPU::opcode_0x1F() { RRA(); }


/* INC */
void CPU::opcode_0x04() { INC_r8(b); }
void CPU::opcode_0x14() { INC_r8(d); }
void CPU::opcode_0x24() { INC_r8(h); }
void CPU::opcode_0x34()
{
  word address = hl.get();
  byte result = mmu->read(address) + 1;

  mmu->write(address, result);

  f.write((uint8_t)Flag::Z_ZERO, result == 0);
  f.write((uint8_t)Flag::N_SUBTRACT, false);
  f.write((uint8_t)Flag::H_HALFCARRY, (result & 0x0F) == 0x00);
}

void CPU::opcode_0x0C() { INC_r8(c); }
void CPU::opcode_0x1C() { INC_r8(e); }
void CPU::opcode_0x2C() { INC_r8(l); }
void CPU::opcode_0x3C() { INC_r8(a); }


/* LD opcode mappings */
void CPU::opcode_0x02() { LD_r16_r8(bc, a); }
void CPU::opcode_0x12() { LD_r16_r8(de, a); }
void CPU::opcode_0x22() { LD_r16_r8(hl, a); hl.increment(); } // HL+

void CPU::opcode_0x32() { LD_r16_r8(hl, a); hl.decrement(); } // HL-

void CPU::opcode_0x06() { LD_r8_n8(b); }
void CPU::opcode_0x16() { LD_r8_n8(d); }
void CPU::opcode_0x26() { LD_r8_n8(h); }
void CPU::opcode_0x36() { LD_addr16_n8(hl); }

void CPU::opcode_0x0A() { LD_r8_r16(a, bc); }
void CPU::opcode_0x1A() { LD_r8_r16(a, de); }
void CPU::opcode_0x2A() { LD_r8_r16(a, hl); hl.increment(); }
void CPU::opcode_0x3A() { LD_r8_r16(a, hl); hl.decrement(); }

void CPU::opcode_0x0E() { LD_r8_n8(c); }
void CPU::opcode_0x1E() { LD_r8_n8(e); }
void CPU::opcode_0x2E() { LD_r8_n8(l); }
void CPU::opcode_0x3E() { LD_r8_n8(a); }

void CPU::opcode_0x40() { LD_r8_r8(b, b); }
void CPU::opcode_0x41() { LD_r8_r8(b, c); }
void CPU::opcode_0x42() { LD_r8_r8(b, d); }
void CPU::opcode_0x43() { LD_r8_r8(b, e); }
void CPU::opcode_0x44() { LD_r8_r8(b, h); }
void CPU::opcode_0x45() { LD_r8_r8(b, l); }
void CPU::opcode_0x46() { LD_r8_r16(b, hl); }
void CPU::opcode_0x47() { LD_r8_r8(b, a); }

void CPU::opcode_0x48() { LD_r8_r8(c, b); }
void CPU::opcode_0x49() { LD_r8_r8(c, c); }
void CPU::opcode_0x4A() { LD_r8_r8(c, d); }
void CPU::opcode_0x4B() { LD_r8_r8(c, e); }
void CPU::opcode_0x4C() { LD_r8_r8(c, h); }
void CPU::opcode_0x4D() { LD_r8_r8(c, l); }
void CPU::opcode_0x4E() { LD_r8_r16(c, hl); }
void CPU::opcode_0x4F() { LD_r8_r8(c, a); }

void CPU::opcode_0x50() { LD_r8_r8(d, b); }
void CPU::opcode_0x51() { LD_r8_r8(d, c); }
void CPU::opcode_0x52() { LD_r8_r8(d, d); }
void CPU::opcode_0x53() { LD_r8_r8(d, e); }
void CPU::opcode_0x54() { LD_r8_r8(d, h); }
void CPU::opcode_0x55() { LD_r8_r8(d, l); }
void CPU::opcode_0x56() { LD_r8_r16(d, hl); }
void CPU::opcode_0x57() { LD_r8_r8(d, a); }

void CPU::opcode_0x58() { LD_r8_r8(e, b); }
void CPU::opcode_0x59() { LD_r8_r8(e, c); }
void CPU::opcode_0x5A() { LD_r8_r8(e, d); }
void CPU::opcode_0x5B() { LD_r8_r8(e, e); }
void CPU::opcode_0x5C() { LD_r8_r8(e, h); }
void CPU::opcode_0x5D() { LD_r8_r8(e, l); }
void CPU::opcode_0x5E() { LD_r8_r16(e, hl); }
void CPU::opcode_0x5F() { LD_r8_r8(e, a); }

void CPU::opcode_0x60() { LD_r8_r8(h, b); }
void CPU::opcode_0x61() { LD_r8_r8(h, c); }
void CPU::opcode_0x62() { LD_r8_r8(h, d); }
void CPU::opcode_0x63() { LD_r8_r8(h, e); }
void CPU::opcode_0x64() { LD_r8_r8(h, h); }
void CPU::opcode_0x65() { LD_r8_r8(h, l); }
void CPU::opcode_0x66() { LD_r8_r16(h, hl); }
void CPU::opcode_0x67() { LD_r8_r8(h, a); }

void CPU::opcode_0x68() { LD_r8_r8(l, b); }
void CPU::opcode_0x69() { LD_r8_r8(l, c); }
void CPU::opcode_0x6A() { LD_r8_r8(l, d); }
void CPU::opcode_0x6B() { LD_r8_r8(l, e); }
void CPU::opcode_0x6C() { LD_r8_r8(l, h); }
void CPU::opcode_0x6D() { LD_r8_r8(l, l); }
void CPU::opcode_0x6E() { LD_r8_r16(l, hl); }
void CPU::opcode_0x6F() { LD_r8_r8(l, a); }

void CPU::opcode_0x70() { LD_r16_r8(hl, b); }
void CPU::opcode_0x71() { LD_r16_r8(hl, c); }
void CPU::opcode_0x72() { LD_r16_r8(hl, d); }
void CPU::opcode_0x73() { LD_r16_r8(hl, e); }
void CPU::opcode_0x74() { LD_r16_r8(hl, h); }
void CPU::opcode_0x75() { LD_r16_r8(hl, l); }
void CPU::opcode_0x77() { LD_r16_r8(hl, a); }

void CPU::opcode_0x78() { LD_r8_r8(a, b); }
void CPU::opcode_0x79() { LD_r8_r8(a, c); }
void CPU::opcode_0x7A() { LD_r8_r8(a, d); }
void CPU::opcode_0x7B() { LD_r8_r8(a, e); }
void CPU::opcode_0x7C() { LD_r8_r8(a, h); }
void CPU::opcode_0x7D() { LD_r8_r8(a, l); }
void CPU::opcode_0x7E() { LD_r8_r16(a, hl); }
void CPU::opcode_0x7F() { LD_r8_r8(a, a); }

void CPU::opcode_0xE2()
{
  word addr = c.get() + 0xFF00;
  mmu->write(addr, a.get());
}

void CPU::opcode_0xF2()
{
  word val = mmu->read(0xFF00 + c.get());
  a.set(val);
}

void CPU::opcode_0xEA() { LD_nn16_r8(a); }
void CPU::opcode_0xFA() { LD_r8_nn16(a); }


/* LDH */
void CPU::opcode_0xE0() { LDH_r8_n8(a); }
void CPU::opcode_0xF0() { LDH_n8_r8(a); }


/* LD 16 */
void CPU::opcode_0x01() { LD_r16_nn16(bc); }
void CPU::opcode_0x11() { LD_r16_nn16(de); }
void CPU::opcode_0x21() { LD_r16_nn16(hl); }
void CPU::opcode_0x31() { LD_r16_nn16(sp); }

void CPU::opcode_0x08() { LD_nn16_r16(sp); } // SP -> nn16

void CPU::opcode_0xF8()
{
  word reg = sp.get();
  int8_t e = read_pc_signed();

  int result = static_cast<int>(reg + e);

  f.write((uint8_t)Flag::Z_ZERO, false);
  f.write((uint8_t)Flag::N_SUBTRACT, false);
  f.write((uint8_t)Flag::H_HALFCARRY, (reg ^ e ^ (result & 0xFFFF) & 0x10) == 0x10);
  f.write((uint8_t)Flag::C_CARRY, (reg ^ e ^ (result & 0xFFFF) & 0x100) == 0x100);

  hl.set(result);
}
void CPU::opcode_0xF9() {
  sp.set(hl.get());
}


/* JP */
void CPU::opcode_0xC2() { JP(!f.read((uint8_t)Flag::Z_ZERO)); }
void CPU::opcode_0xD2() { JP(!f.read((uint8_t)Flag::C_CARRY)); }
void CPU::opcode_0xCA() { JP(f.read((uint8_t)Flag::Z_ZERO)); }
void CPU::opcode_0xDA() { JP(f.read((uint8_t)Flag::C_CARRY)); }
void CPU::opcode_0xE9() { JP_hl(); }
void CPU::opcode_0xC3() { JP(); }


/* JR */
void CPU::opcode_0x20() { JR_cc_e(!f.read((uint8_t)Flag::Z_ZERO)); }
void CPU::opcode_0x30() { JR_cc_e(!f.read((uint8_t)Flag::C_CARRY)); }

void CPU::opcode_0x18() { JR_cc_e(); }
void CPU::opcode_0x28() { JR_cc_e(f.read((uint8_t)Flag::Z_ZERO)); }
void CPU::opcode_0x38() { JR_cc_e(f.read((uint8_t)Flag::C_CARRY)); }

/* CALL */
void CPU::opcode_0xCD() { CALL_nn(); }

void CPU::opcode_0xCC() { CALL_nn(f.read((uint8_t)Flag::Z_ZERO)); }
void CPU::opcode_0xDC() { CALL_nn(f.read((uint8_t)Flag::C_CARRY)); }

void CPU::opcode_0xC4() { CALL_nn(!f.read((uint8_t)Flag::Z_ZERO)); }
void CPU::opcode_0xD4() { CALL_nn(!f.read((uint8_t)Flag::C_CARRY)); }


/* RET */
void CPU::opcode_0xC9() { RET_cc(); }
void CPU::opcode_0xC8() { RET_cc(f.read((uint8_t)Flag::Z_ZERO)); }
void CPU::opcode_0xD8() { RET_cc(f.read((uint8_t)Flag::C_CARRY)); }
void CPU::opcode_0xC0() { RET_cc(!f.read((uint8_t)Flag::Z_ZERO)); }
void CPU::opcode_0xD0() { RET_cc(!f.read((uint8_t)Flag::C_CARRY)); }


/* POP */
void CPU::opcode_0xC1() { stack_pop(bc); }
void CPU::opcode_0xD1() { stack_pop(de); }
void CPU::opcode_0xE1() { stack_pop(hl); }
void CPU::opcode_0xF1() { stack_pop(af); }


/* PUSH */
void CPU::opcode_0xC5() { stack_push(bc); }
void CPU::opcode_0xD5() { stack_push(de); }
void CPU::opcode_0xE5() { stack_push(hl); }
void CPU::opcode_0xF5() { stack_push(af); }


/* AND */
void CPU::opcode_0xA0() { AND_r8(b); }
void CPU::opcode_0xA1() { AND_r8(c); }
void CPU::opcode_0xA2() { AND_r8(d); }
void CPU::opcode_0xA3() { AND_r8(e); }
void CPU::opcode_0xA4() { AND_r8(h); }
void CPU::opcode_0xA5() { AND_r8(l); }
void CPU::opcode_0xA7() { AND_r8(a); }
void CPU::opcode_0xA6() { AND_r16(hl); }
void CPU::opcode_0xE6() { AND_n8(); }


/* DEC */
void CPU::opcode_0x05() { DEC_r8(b); }
void CPU::opcode_0x15() { DEC_r8(d); }
void CPU::opcode_0x25() { DEC_r8(h); }
void CPU::opcode_0x35() { DEC_hl(); }

void CPU::opcode_0x0D() { DEC_r8(c); }
void CPU::opcode_0x1D() { DEC_r8(e); }
void CPU::opcode_0x2D() { DEC_r8(l); }
void CPU::opcode_0x3D() { DEC_r8(a); }


/* INC 16 */
void CPU::opcode_0x33() { INC_r16(sp); }
void CPU::opcode_0x23() { INC_r16(hl); }
void CPU::opcode_0x13() { INC_r16(de); }
void CPU::opcode_0x03() { INC_r16(bc); }

/* DEC 16 */
void CPU::opcode_0x3B() { DEC_r16(sp); }
void CPU::opcode_0x2B() { DEC_r16(hl); }
void CPU::opcode_0x1B() { DEC_r16(de); }
void CPU::opcode_0x0B() { DEC_r16(bc); }


/* OR */
void CPU::opcode_0xB7() { OR_r8(a); }
void CPU::opcode_0xB5() { OR_r8(l); }
void CPU::opcode_0xB4() { OR_r8(h); }
void CPU::opcode_0xB3() { OR_r8(e); }
void CPU::opcode_0xB2() { OR_r8(d); }
void CPU::opcode_0xB1() { OR_r8(c); }
void CPU::opcode_0xB0() { OR_r8(b); }
void CPU::opcode_0xF6() { OR_n8(); }
void CPU::opcode_0xB6() { OR_r16(hl); }


/* CP */
void CPU::opcode_0xBF() { CP_r8(a); }
void CPU::opcode_0xBD() { CP_r8(l); }
void CPU::opcode_0xBC() { CP_r8(h); }
void CPU::opcode_0xBB() { CP_r8(e); }
void CPU::opcode_0xBA() { CP_r8(d); }
void CPU::opcode_0xB9() { CP_r8(c); }
void CPU::opcode_0xB8() { CP_r8(b); }

void CPU::opcode_0xFE() { CP_n8(); }
void CPU::opcode_0xBE() { CP_r16(hl); }


/* XOR */
void CPU::opcode_0xAF() { XOR_r8(a); }
void CPU::opcode_0xAD() { XOR_r8(l); }
void CPU::opcode_0xAC() { XOR_r8(h); }
void CPU::opcode_0xAB() { XOR_r8(e); }
void CPU::opcode_0xAA() { XOR_r8(d); }
void CPU::opcode_0xA9() { XOR_r8(c); }
void CPU::opcode_0xA8() { XOR_r8(b); }

void CPU::opcode_0xEE() { XOR_n8(); }
void CPU::opcode_0xAE() { XOR_r16(hl); }


/* ADD */
void CPU::opcode_0x87() { ADD_r8(a); }
void CPU::opcode_0x85() { ADD_r8(l); }
void CPU::opcode_0x84() { ADD_r8(h); }
void CPU::opcode_0x83() { ADD_r8(e); }
void CPU::opcode_0x82() { ADD_r8(d); }
void CPU::opcode_0x81() { ADD_r8(c); }
void CPU::opcode_0x80() { ADD_r8(b); }

void CPU::opcode_0xC6() { ADD_n8(); }
void CPU::opcode_0x86() { ADD_r16(hl); }

void CPU::opcode_0x09() { ADD_hl_r16(bc); }
void CPU::opcode_0x19() { ADD_hl_r16(de); }
void CPU::opcode_0x29() { ADD_hl_r16(hl); }
void CPU::opcode_0x39() { ADD_hl_r16(sp); }


/* SUB */
void CPU::opcode_0x97() { SUB_r8(a); }
void CPU::opcode_0x95() { SUB_r8(l); }
void CPU::opcode_0x94() { SUB_r8(h); }
void CPU::opcode_0x93() { SUB_r8(e); }
void CPU::opcode_0x92() { SUB_r8(d); }
void CPU::opcode_0x91() { SUB_r8(c); }
void CPU::opcode_0x90() { SUB_r8(b); }

void CPU::opcode_0xD6() { SUB_n8(); }
void CPU::opcode_0x96() { SUB_r16(hl); }


/* ADC */
void CPU::opcode_0x8F() { ADC_r8(a); }
void CPU::opcode_0x8D() { ADC_r8(l); }
void CPU::opcode_0x8C() { ADC_r8(h); }
void CPU::opcode_0x8B() { ADC_r8(e); }
void CPU::opcode_0x8A() { ADC_r8(d); }
void CPU::opcode_0x89() { ADC_r8(c); }
void CPU::opcode_0x88() { ADC_r8(b); }

void CPU::opcode_0xCE() { ADC_n8(); }
void CPU::opcode_0x8E() { ADC_r16(hl); }


/* SBC */
void CPU::opcode_0x9F() { SBC_r8(a); }
void CPU::opcode_0x9D() { SBC_r8(l); }
void CPU::opcode_0x9C() { SBC_r8(h); }
void CPU::opcode_0x9B() { SBC_r8(e); }
void CPU::opcode_0x9A() { SBC_r8(d); }
void CPU::opcode_0x99() { SBC_r8(c); }
void CPU::opcode_0x98() { SBC_r8(b); }

void CPU::opcode_0xDE() { SBC_n8(); }
void CPU::opcode_0x9E() { SBC_r16(hl); }

/* ======================================== */

/* MISC */
void CPU::RLCA()
{
  a.set(RLC(a.get()));
  f.write((uint8_t)Flag::Z_ZERO, false);
}
void CPU::RLA()
{
  a.set(RL(a.get()));
  f.write((uint8_t)Flag::Z_ZERO, false);
}
void CPU::RRCA()
{
  a.set(RRC(a.get()));
  f.write((uint8_t)Flag::Z_ZERO, false);
}
void CPU::RRA()
{
  a.set(RR(a.get()));
  f.write((uint8_t)Flag::Z_ZERO, false);
}


/* INC */
void CPU::INC_r8(ByteRegister& reg)
{
  reg.increment();
  f.write((uint8_t)Flag::Z_ZERO, reg.get() == 0);
  f.write((uint8_t)Flag::N_SUBTRACT, false);
  f.write((uint8_t)Flag::H_HALFCARRY, (reg.get() & 0x0F) == 0x00);
}

/* LD */
void CPU::LD_r8_r8(ByteRegister& reg1, ByteRegister& reg2)
{
  reg1.set(reg2.get());
}

void CPU::LD_r8_n8(ByteRegister& reg)
{
  byte value = read_pc();
  reg.set(value);
}

void CPU::LD_r8_r16(ByteRegister& reg, RegisterPair& reg16)
{
  word addr = reg16.get();
  reg.set(mmu->read(addr));
}

void CPU::LD_r16_r8(RegisterPair& reg16, ByteRegister& reg)
{
  mmu->write(reg16.get(), reg.get());
}

void CPU::LD_addr16_n8(RegisterPair& reg)
{
  byte value = read_pc();
  word addr = reg.get();
  mmu->write(addr, value);
}

void CPU::LD_nn16_r8(ByteRegister& reg)
{
  word addr = mmu->read(pc.get());
  pc.increment();
  addr |= mmu->read(pc.get()) << 8;
  pc.increment();

  mmu->write(addr, reg.get());
}

void CPU::LD_r8_nn16(ByteRegister& reg)
{
  word addr = mmu->read(pc.get());
  pc.increment();
  addr |= mmu->read(pc.get()) << 8;
  pc.increment();

  reg.set(mmu->read(addr));
}


/* LDH */
void CPU::LDH_r8_n8(ByteRegister& reg)
{
  byte value = mmu->read(pc.get());
  pc.increment();
  mmu->write(0xFF00 + value, reg.get());
}

void CPU::LDH_n8_r8(ByteRegister& reg)
{
  byte value = mmu->read(pc.get());
  pc.increment();
  reg.set(mmu->read(0xFF00 + value));
}

/* TEMPORARY */
void CPU::LD_r16_nn16(WordRegister& reg)
{
  word addr = mmu->read(pc.get());
  pc.increment();
  addr |= mmu->read(pc.get()) << 8;
  pc.increment();

  reg.set(addr);
}

void CPU::LD_nn16_r16(WordRegister& reg)
{
  word addr = mmu->read(pc.get());
  pc.increment();
  addr |= mmu->read(pc.get()) << 8;

  mmu->write(addr, reg.get());
}

/* LD 16 */
void CPU::LD_r16_nn16(RegisterPair& reg)
{
  word addr = mmu->read(pc.get());
  pc.increment();
  addr |= mmu->read(pc.get()) << 8;
  pc.increment();

  reg.set(addr);
}

void CPU::LD_nn16_r16(RegisterPair& reg)
{
  word addr = mmu->read(pc.get());
  pc.increment();
  addr |= mmu->read(pc.get()) << 8;

  mmu->write(addr, reg.get());
}


/* JP */
void CPU::JP(bool conditional)
{
  if (conditional) {
    cond_cycles = true;

    pc.set(read_pc_word());
  }
}
void CPU::JP_hl()
{
  pc.set(hl.get());
}

/* JR */
void CPU::JR_cc_e(bool conditional)
{
  int8_t offset = read_pc_signed();

  if (offset == -2) exit(0);

  if (conditional) {
    cond_cycles = true;

    word result = static_cast<word>(pc.get() + offset);
    pc.set(result);
  }
}


/* CALL */
void CPU::CALL_nn(bool conditional)
{

  word nn = read_pc_word();

  if (conditional) {
    cond_cycles = true;

    stack_push(pc);
    pc.set(nn);
  }
}


/* RET */
void CPU::RET_cc(bool conditional)
{
  if (conditional) {
    cond_cycles = true;

    stack_pop(pc);
  }
}


/* AND */
void CPU::AND(byte value)
{
  a.set(a.get() & value);
  f.write((uint8_t)Flag::Z_ZERO, a.get() == 0);
  f.write((uint8_t)Flag::N_SUBTRACT, false);
  f.write((uint8_t)Flag::H_HALFCARRY, true);
  f.write((uint8_t)Flag::C_CARRY, false);
}
void CPU::AND_r8(ByteRegister& reg)
{
  AND(reg.get());
}
void CPU::AND_r16(RegisterPair& reg)
{
  AND(mmu->read(reg.get()));
}

void CPU::AND_n8()
{
  AND(read_pc());
}


/* TEMPORARY */
void CPU::AND_r16(WordRegister& reg)
{
  AND(mmu->read(reg.get()));
}


/* DEC */
void CPU::DEC_r8(ByteRegister& reg)
{
  reg.decrement();
  f.write((uint8_t)Flag::Z_ZERO, reg.get() == 0);
  f.write((uint8_t)Flag::N_SUBTRACT, true);
  f.write((uint8_t)Flag::H_HALFCARRY, (reg.get() & 0x0F) == 0x0F);
}
void CPU::DEC_hl()
{
  word address = hl.get();
  byte result = mmu->read(address) - 1;

  mmu->write(address, result);

  f.write((uint8_t)Flag::Z_ZERO, hl.get() == 0);
  f.write((uint8_t)Flag::N_SUBTRACT, true);
  f.write((uint8_t)Flag::H_HALFCARRY, (hl.get() & 0x0F) == 0x0F);
}

/* TEMPORARY */
void CPU::INC_r16(WordRegister& reg)
{
  reg.increment();
}
void CPU::DEC_r16(WordRegister& reg)
{
  reg.decrement();
}

/* INC 16 */
void CPU::INC_r16(RegisterPair& reg)
{
  reg.increment();
}


/* DEC 16 */
void CPU::DEC_r16(RegisterPair& reg)
{
  reg.decrement();
}


/* OR */
void CPU::OR(byte value)
{
  a.set(a.get() | value);

  f.write((uint8_t)Flag::Z_ZERO, a.get() == 0);
  f.write((uint8_t)Flag::N_SUBTRACT, false);
  f.write((uint8_t)Flag::H_HALFCARRY, false);
  f.write((uint8_t)Flag::C_CARRY, false);
}
void CPU::OR_r8(ByteRegister& reg)
{
  OR(reg.get());
}
void CPU::OR_n8()
{
  OR(read_pc());
}
void CPU::OR_r16(RegisterPair& reg)
{
  OR(mmu->read(reg.get()));
}


/* CP */
void CPU::CP(byte value)
{
  f.write((uint8_t)Flag::Z_ZERO, a.get() == value);
  f.write((uint8_t)Flag::N_SUBTRACT, true);
  f.write((uint8_t)Flag::H_HALFCARRY, (a.get() & 0xF) - (value & 0xF) < 0);
  f.write((uint8_t)Flag::C_CARRY, a.get() < value);
}
void CPU::CP_r8(ByteRegister& reg)
{
  CP(reg.get());
}
void CPU::CP_n8()
{
  CP(read_pc());
}
void CPU::CP_r16(RegisterPair& reg)
{
  CP(mmu->read(reg.get()));
}


/* XOR */
void CPU::XOR(byte value)
{
  a.set(a.get() ^ value);
  f.write((uint8_t)Flag::Z_ZERO, a.get() == value);
  f.write((uint8_t)Flag::N_SUBTRACT, false);
  f.write((uint8_t)Flag::H_HALFCARRY, false);
  f.write((uint8_t)Flag::C_CARRY, false);
}
void CPU::XOR_r8(ByteRegister& reg)
{
  XOR(reg.get());
}
void CPU::XOR_n8()
{
  XOR(read_pc());
}
void CPU::XOR_r16(RegisterPair& reg)
{
  XOR(mmu->read(reg.get()));
}


/* ADD */
void CPU::ADD(byte value)
{
  byte reg = a.get();
  uint result = reg + value;

  a.set(static_cast<byte>(result));

  f.write((uint8_t)Flag::Z_ZERO, a.get() == 0);
  f.write((uint8_t)Flag::N_SUBTRACT, false);
  f.write((uint8_t)Flag::H_HALFCARRY, ((reg & 0xF) + (value & 0xF) > 0xF));
  f.write((uint8_t)Flag::C_CARRY, (result & 0x100) != 0);

}
void CPU::ADD_r8(ByteRegister& reg)
{
  ADD(reg.get());
}
void CPU::ADD_n8()
{
  ADD(read_pc());
}
void CPU::ADD_r16(RegisterPair& reg)
{
  ADD(mmu->read(reg.get()));
}
void CPU::ADD_hl_r16(RegisterPair& reg)
{
  uint32_t result_full = reg.get() + hl.get();
  word result = static_cast<word>(result_full);

  f.write((uint8_t)Flag::N_SUBTRACT, false);
  f.write((uint8_t)Flag::H_HALFCARRY, (reg.get() ^ hl.get() ^ (result_full & 0xFFFF)) & 0x1000);
  f.write((uint8_t)Flag::C_CARRY, result_full > 0xFFFF);

  reg.set(result);
}
void CPU::ADD_hl_r16(WordRegister& reg)
{
  uint32_t result_full = reg.get() + hl.get();
  word result = static_cast<word>(result_full);

  f.write((uint8_t)Flag::N_SUBTRACT, false);
  f.write((uint8_t)Flag::H_HALFCARRY, (reg.get() ^ hl.get() ^ (result_full & 0xFFFF)) & 0x1000);
  f.write((uint8_t)Flag::C_CARRY, result_full > 0xFFFF);

  reg.set(result);
}


/* SUB */
void CPU::SUB(byte value)
{
  byte reg = a.get();
  int result = reg - value;

  a.set(static_cast<byte>(result));

  f.write((uint8_t)Flag::Z_ZERO, a.get() == 0);
  f.write((uint8_t)Flag::N_SUBTRACT, false);
  f.write((uint8_t)Flag::H_HALFCARRY, ((reg & 0xF) - (value & 0xF) < 0));
  f.write((uint8_t)Flag::C_CARRY, result < 0);
}
void CPU::SUB_r8(ByteRegister& reg)
{
  SUB(reg.get());
}
void CPU::SUB_n8()
{
  SUB(read_pc());
}
void CPU::SUB_r16(RegisterPair& reg)
{
  SUB(mmu->read(reg.get()));
}


/* ADC */
void CPU::ADC(byte value)
{
  byte reg = a.get();
  byte carry = f.read((uint8_t)Flag::C_CARRY);

  uint result_full = reg + value + carry;
  byte result = static_cast<int8_t>(result_full);

  a.set(result);

  f.write((uint8_t)Flag::Z_ZERO, result == 0);
  f.write((uint8_t)Flag::N_SUBTRACT, false);
  f.write((uint8_t)Flag::H_HALFCARRY, ((reg & 0xF) + (value & 0xF) + carry) > 0xF);
  f.write((uint8_t)Flag::C_CARRY, result_full > 0xFF);
}
void CPU::ADC_r8(ByteRegister& reg)
{
  ADC(reg.get());
}
void CPU::ADC_n8()
{
  ADC(read_pc());
}
void CPU::ADC_r16(RegisterPair& reg)
{
  ADC(mmu->read(reg.get()));
}


/* SBC */
void CPU::SBC(byte value)
{
  byte reg = a.get();
  byte carry = f.read((uint8_t)Flag::C_CARRY);

  int result_full = reg - value - carry;
  byte result = static_cast<uint8_t>(result_full);

  a.set(result);

  f.write((uint8_t)Flag::Z_ZERO, a.get() == 0);
  f.write((uint8_t)Flag::N_SUBTRACT, true);
  f.write((uint8_t)Flag::H_HALFCARRY, result_full < 0);
  f.write((uint8_t)Flag::C_CARRY, ((reg & 0xF) - (value & 0xF) - carry) < 0);
}
void CPU::SBC_r8(ByteRegister& reg)
{
  SBC(reg.get());
}
void CPU::SBC_n8()
{
  SBC(read_pc());
}
void CPU::SBC_r16(RegisterPair& reg)
{
  SBC(mmu->read(reg.get()));
}




void CPU::opcode_cb_0xFF() { SET_r8(a, 7); }
void CPU::opcode_cb_0xFE() { SET_hl(7); }
void CPU::opcode_cb_0xFD() { SET_r8(l, 7); }
void CPU::opcode_cb_0xFC() { SET_r8(h, 7); }
void CPU::opcode_cb_0xFB() { SET_r8(e, 7); }
void CPU::opcode_cb_0xFA() { SET_r8(d, 7); }
void CPU::opcode_cb_0xF9() { SET_r8(c, 7); }
void CPU::opcode_cb_0xF8() { SET_r8(b, 7); }
void CPU::opcode_cb_0xF7() { SET_r8(a, 6); }
void CPU::opcode_cb_0xF6() { SET_hl(6); }
void CPU::opcode_cb_0xF5() { SET_r8(l, 6); }
void CPU::opcode_cb_0xF4() { SET_r8(h, 6); }
void CPU::opcode_cb_0xF3() { SET_r8(e, 6); }
void CPU::opcode_cb_0xF2() { SET_r8(d, 6); }
void CPU::opcode_cb_0xF1() { SET_r8(c, 6); }
void CPU::opcode_cb_0xF0() { SET_r8(b, 6); }
void CPU::opcode_cb_0xEF() { SET_r8(a, 5); }
void CPU::opcode_cb_0xEE() { SET_hl(5); }
void CPU::opcode_cb_0xED() { SET_r8(l, 5); }
void CPU::opcode_cb_0xEC() { SET_r8(h, 5); }
void CPU::opcode_cb_0xEB() { SET_r8(e, 5); }
void CPU::opcode_cb_0xEA() { SET_r8(d, 5); }
void CPU::opcode_cb_0xE9() { SET_r8(c, 5); }
void CPU::opcode_cb_0xE8() { SET_r8(b, 5); }
void CPU::opcode_cb_0xE7() { SET_r8(a, 4); }
void CPU::opcode_cb_0xE6() { SET_hl(4); }
void CPU::opcode_cb_0xE5() { SET_r8(l, 4); }
void CPU::opcode_cb_0xE4() { SET_r8(h, 4); }
void CPU::opcode_cb_0xE3() { SET_r8(e, 4); }
void CPU::opcode_cb_0xE2() { SET_r8(d, 4); }
void CPU::opcode_cb_0xE1() { SET_r8(c, 4); }
void CPU::opcode_cb_0xE0() { SET_r8(b, 4); }
void CPU::opcode_cb_0xDF() { SET_r8(a, 3); }
void CPU::opcode_cb_0xDE() { SET_hl(3); }
void CPU::opcode_cb_0xDD() { SET_r8(l, 3); }
void CPU::opcode_cb_0xDC() { SET_r8(h, 3); }
void CPU::opcode_cb_0xDB() { SET_r8(e, 3); }
void CPU::opcode_cb_0xDA() { SET_r8(d, 3); }
void CPU::opcode_cb_0xD9() { SET_r8(c, 3); }
void CPU::opcode_cb_0xD8() { SET_r8(b, 3); }
void CPU::opcode_cb_0xD7() { SET_r8(a, 2); }
void CPU::opcode_cb_0xD6() { SET_hl(2); }
void CPU::opcode_cb_0xD5() { SET_r8(l, 2); }
void CPU::opcode_cb_0xD4() { SET_r8(h, 2); }
void CPU::opcode_cb_0xD3() { SET_r8(e, 2); }
void CPU::opcode_cb_0xD2() { SET_r8(d, 2); }
void CPU::opcode_cb_0xD1() { SET_r8(c, 2); }
void CPU::opcode_cb_0xD0() { SET_r8(b, 2); }
void CPU::opcode_cb_0xCF() { SET_r8(a, 1); }
void CPU::opcode_cb_0xCE() { SET_hl(1); }
void CPU::opcode_cb_0xCD() { SET_r8(l, 1); }
void CPU::opcode_cb_0xCC() { SET_r8(h, 1); }
void CPU::opcode_cb_0xCB() { SET_r8(e, 1); }
void CPU::opcode_cb_0xCA() { SET_r8(d, 1); }
void CPU::opcode_cb_0xC9() { SET_r8(c, 1); }
void CPU::opcode_cb_0xC8() { SET_r8(b, 1); }
void CPU::opcode_cb_0xC7() { SET_r8(a, 0); }
void CPU::opcode_cb_0xC6() { SET_hl(0); }
void CPU::opcode_cb_0xC5() { SET_r8(l, 0); }
void CPU::opcode_cb_0xC4() { SET_r8(h, 0); }
void CPU::opcode_cb_0xC3() { SET_r8(e, 0); }
void CPU::opcode_cb_0xC2() { SET_r8(d, 0); }
void CPU::opcode_cb_0xC1() { SET_r8(c, 0); }
void CPU::opcode_cb_0xC0() { SET_r8(b, 0); }
void CPU::opcode_cb_0xBF() { RES_r8(a, 7); }
void CPU::opcode_cb_0xBE() { RES_hl(7); }
void CPU::opcode_cb_0xBD() { RES_r8(l, 7); }
void CPU::opcode_cb_0xBC() { RES_r8(h, 7); }
void CPU::opcode_cb_0xBB() { RES_r8(e, 7); }
void CPU::opcode_cb_0xBA() { RES_r8(d, 7); }
void CPU::opcode_cb_0xB9() { RES_r8(c, 7); }
void CPU::opcode_cb_0xB8() { RES_r8(b, 7); }
void CPU::opcode_cb_0xB7() { RES_r8(a, 6); }
void CPU::opcode_cb_0xB6() { RES_hl(6); }
void CPU::opcode_cb_0xB5() { RES_r8(l, 6); }
void CPU::opcode_cb_0xB4() { RES_r8(h, 6); }
void CPU::opcode_cb_0xB3() { RES_r8(e, 6); }
void CPU::opcode_cb_0xB2() { RES_r8(d, 6); }
void CPU::opcode_cb_0xB1() { RES_r8(c, 6); }
void CPU::opcode_cb_0xB0() { RES_r8(b, 6); }
void CPU::opcode_cb_0xAF() { RES_r8(a, 5); }
void CPU::opcode_cb_0xAE() { RES_hl(5); }
void CPU::opcode_cb_0xAD() { RES_r8(l, 5); }
void CPU::opcode_cb_0xAC() { RES_r8(h, 5); }
void CPU::opcode_cb_0xAB() { RES_r8(e, 5); }
void CPU::opcode_cb_0xAA() { RES_r8(d, 5); }
void CPU::opcode_cb_0xA9() { RES_r8(c, 5); }
void CPU::opcode_cb_0xA8() { RES_r8(b, 5); }
void CPU::opcode_cb_0xA7() { RES_r8(a, 4); }
void CPU::opcode_cb_0xA6() { RES_hl(4); }
void CPU::opcode_cb_0xA5() { RES_r8(l, 4); }
void CPU::opcode_cb_0xA4() { RES_r8(h, 4); }
void CPU::opcode_cb_0xA3() { RES_r8(e, 4); }
void CPU::opcode_cb_0xA2() { RES_r8(d, 4); }
void CPU::opcode_cb_0xA1() { RES_r8(c, 4); }
void CPU::opcode_cb_0xA0() { RES_r8(b, 4); }
void CPU::opcode_cb_0x9F() { RES_r8(a, 3); }
void CPU::opcode_cb_0x9E() { RES_hl(3); }
void CPU::opcode_cb_0x9D() { RES_r8(l, 3); }
void CPU::opcode_cb_0x9C() { RES_r8(h, 3); }
void CPU::opcode_cb_0x9B() { RES_r8(e, 3); }
void CPU::opcode_cb_0x9A() { RES_r8(d, 3); }
void CPU::opcode_cb_0x99() { RES_r8(c, 3); }
void CPU::opcode_cb_0x98() { RES_r8(b, 3); }
void CPU::opcode_cb_0x97() { RES_r8(a, 2); }
void CPU::opcode_cb_0x96() { RES_hl(2); }
void CPU::opcode_cb_0x95() { RES_r8(l, 2); }
void CPU::opcode_cb_0x94() { RES_r8(h, 2); }
void CPU::opcode_cb_0x93() { RES_r8(e, 2); }
void CPU::opcode_cb_0x92() { RES_r8(d, 2); }
void CPU::opcode_cb_0x91() { RES_r8(c, 2); }
void CPU::opcode_cb_0x90() { RES_r8(b, 2); }
void CPU::opcode_cb_0x8F() { RES_r8(a, 1); }
void CPU::opcode_cb_0x8E() { RES_hl(1); }
void CPU::opcode_cb_0x8D() { RES_r8(l, 1); }
void CPU::opcode_cb_0x8C() { RES_r8(h, 1); }
void CPU::opcode_cb_0x8B() { RES_r8(e, 1); }
void CPU::opcode_cb_0x8A() { RES_r8(d, 1); }
void CPU::opcode_cb_0x89() { RES_r8(c, 1); }
void CPU::opcode_cb_0x88() { RES_r8(b, 1); }
void CPU::opcode_cb_0x87() { RES_r8(a, 0); }
void CPU::opcode_cb_0x86() { RES_hl(0); }
void CPU::opcode_cb_0x85() { RES_r8(l, 0); }
void CPU::opcode_cb_0x84() { RES_r8(h, 0); }
void CPU::opcode_cb_0x83() { RES_r8(e, 0); }
void CPU::opcode_cb_0x82() { RES_r8(d, 0); }
void CPU::opcode_cb_0x81() { RES_r8(c, 0); }
void CPU::opcode_cb_0x80() { RES_r8(b, 0); }
void CPU::opcode_cb_0x7F() { BIT_r8(a, 7); }
void CPU::opcode_cb_0x7E() { BIT_hl(7); }
void CPU::opcode_cb_0x7D() { BIT_r8(l, 7); }
void CPU::opcode_cb_0x7C() { BIT_r8(h, 7); }
void CPU::opcode_cb_0x7B() { BIT_r8(e, 7); }
void CPU::opcode_cb_0x7A() { BIT_r8(d, 7); }
void CPU::opcode_cb_0x79() { BIT_r8(c, 7); }
void CPU::opcode_cb_0x78() { BIT_r8(b, 7); }
void CPU::opcode_cb_0x77() { BIT_r8(a, 6); }
void CPU::opcode_cb_0x76() { BIT_hl(6); }
void CPU::opcode_cb_0x75() { BIT_r8(l, 6); }
void CPU::opcode_cb_0x74() { BIT_r8(h, 6); }
void CPU::opcode_cb_0x73() { BIT_r8(e, 6); }
void CPU::opcode_cb_0x72() { BIT_r8(d, 6); }
void CPU::opcode_cb_0x71() { BIT_r8(c, 6); }
void CPU::opcode_cb_0x70() { BIT_r8(b, 6); }
void CPU::opcode_cb_0x6F() { BIT_r8(a, 5); }
void CPU::opcode_cb_0x6E() { BIT_hl(5); }
void CPU::opcode_cb_0x6D() { BIT_r8(l, 5); }
void CPU::opcode_cb_0x6C() { BIT_r8(h, 5); }
void CPU::opcode_cb_0x6B() { BIT_r8(e, 5); }
void CPU::opcode_cb_0x6A() { BIT_r8(d, 5); }
void CPU::opcode_cb_0x69() { BIT_r8(c, 5); }
void CPU::opcode_cb_0x68() { BIT_r8(b, 5); }
void CPU::opcode_cb_0x67() { BIT_r8(a, 4); }
void CPU::opcode_cb_0x66() { BIT_hl(4); }
void CPU::opcode_cb_0x65() { BIT_r8(l, 4); }
void CPU::opcode_cb_0x64() { BIT_r8(h, 4); }
void CPU::opcode_cb_0x63() { BIT_r8(e, 4); }
void CPU::opcode_cb_0x62() { BIT_r8(d, 4); }
void CPU::opcode_cb_0x61() { BIT_r8(c, 4); }
void CPU::opcode_cb_0x60() { BIT_r8(b, 4); }
void CPU::opcode_cb_0x5F() { BIT_r8(a, 3); }
void CPU::opcode_cb_0x5E() { BIT_hl(3); }
void CPU::opcode_cb_0x5D() { BIT_r8(l, 3); }
void CPU::opcode_cb_0x5C() { BIT_r8(h, 3); }
void CPU::opcode_cb_0x5B() { BIT_r8(e, 3); }
void CPU::opcode_cb_0x5A() { BIT_r8(d, 3); }
void CPU::opcode_cb_0x59() { BIT_r8(c, 3); }
void CPU::opcode_cb_0x58() { BIT_r8(b, 3); }
void CPU::opcode_cb_0x57() { BIT_r8(a, 2); }
void CPU::opcode_cb_0x56() { BIT_hl(2); }
void CPU::opcode_cb_0x55() { BIT_r8(l, 2); }
void CPU::opcode_cb_0x54() { BIT_r8(h, 2); }
void CPU::opcode_cb_0x53() { BIT_r8(e, 2); }
void CPU::opcode_cb_0x52() { BIT_r8(d, 2); }
void CPU::opcode_cb_0x51() { BIT_r8(c, 2); }
void CPU::opcode_cb_0x50() { BIT_r8(b, 2); }
void CPU::opcode_cb_0x4F() { BIT_r8(a, 1); }
void CPU::opcode_cb_0x4E() { BIT_hl(1); }
void CPU::opcode_cb_0x4D() { BIT_r8(l, 1); }
void CPU::opcode_cb_0x4C() { BIT_r8(h, 1); }
void CPU::opcode_cb_0x4B() { BIT_r8(e, 1); }
void CPU::opcode_cb_0x4A() { BIT_r8(d, 1); }
void CPU::opcode_cb_0x49() { BIT_r8(c, 1); }
void CPU::opcode_cb_0x48() { BIT_r8(b, 1); }
void CPU::opcode_cb_0x47() { BIT_r8(a, 0); }
void CPU::opcode_cb_0x46() { BIT_hl(0); }
void CPU::opcode_cb_0x45() { BIT_r8(l, 0); }
void CPU::opcode_cb_0x44() { BIT_r8(h, 0); }
void CPU::opcode_cb_0x43() { BIT_r8(e, 0); }
void CPU::opcode_cb_0x42() { BIT_r8(d, 0); }
void CPU::opcode_cb_0x41() { BIT_r8(c, 0); }
void CPU::opcode_cb_0x40() { BIT_r8(b, 0); }
void CPU::opcode_cb_0x3F() { SRL_r8(a); }
void CPU::opcode_cb_0x3E() { SRL_hl(); }
void CPU::opcode_cb_0x3D() { SRL_r8(l); }
void CPU::opcode_cb_0x3C() { SRL_r8(h); }
void CPU::opcode_cb_0x3B() { SRL_r8(e); }
void CPU::opcode_cb_0x3A() { SRL_r8(d); }
void CPU::opcode_cb_0x39() { SRL_r8(c); }
void CPU::opcode_cb_0x38() { SRL_r8(b); }
void CPU::opcode_cb_0x37() { SWAP_r8(a); }
void CPU::opcode_cb_0x36() { SWAP_hl(); }
void CPU::opcode_cb_0x35() { SWAP_r8(l); }
void CPU::opcode_cb_0x34() { SWAP_r8(h); }
void CPU::opcode_cb_0x33() { SWAP_r8(e); }
void CPU::opcode_cb_0x32() { SWAP_r8(d); }
void CPU::opcode_cb_0x31() { SWAP_r8(c); }
void CPU::opcode_cb_0x30() { SWAP_r8(b); }
void CPU::opcode_cb_0x2F() { SRA_r8(a); }
void CPU::opcode_cb_0x2E() { SRA_hl(); }
void CPU::opcode_cb_0x2D() { SRA_r8(l); }
void CPU::opcode_cb_0x2C() { SRA_r8(h); }
void CPU::opcode_cb_0x2B() { SRA_r8(e); }
void CPU::opcode_cb_0x2A() { SRA_r8(d); }
void CPU::opcode_cb_0x29() { SRA_r8(c); }
void CPU::opcode_cb_0x28() { SRA_r8(b); }
void CPU::opcode_cb_0x27() { SLA_r8(a); }
void CPU::opcode_cb_0x26() { SLA_hl(); }
void CPU::opcode_cb_0x25() { SLA_r8(l); }
void CPU::opcode_cb_0x24() { SLA_r8(h); }
void CPU::opcode_cb_0x23() { SLA_r8(e); }
void CPU::opcode_cb_0x22() { SLA_r8(d); }
void CPU::opcode_cb_0x21() { SLA_r8(c); }
void CPU::opcode_cb_0x20() { SLA_r8(b); }
void CPU::opcode_cb_0x1F() { RR_r8(a); }
void CPU::opcode_cb_0x1E() { RR_hl(); }
void CPU::opcode_cb_0x1D() { RR_r8(l); }
void CPU::opcode_cb_0x1C() { RR_r8(h); }
void CPU::opcode_cb_0x1B() { RR_r8(e); }
void CPU::opcode_cb_0x1A() { RR_r8(d); }
void CPU::opcode_cb_0x19() { RR_r8(c); }
void CPU::opcode_cb_0x18() { RR_r8(b); }
void CPU::opcode_cb_0x17() { RL_r8(a); }
void CPU::opcode_cb_0x16() { RL_hl(); }
void CPU::opcode_cb_0x15() { RL_r8(l); }
void CPU::opcode_cb_0x14() { RL_r8(h); }
void CPU::opcode_cb_0x13() { RL_r8(e); }
void CPU::opcode_cb_0x12() { RL_r8(d); }
void CPU::opcode_cb_0x11() { RL_r8(c); }
void CPU::opcode_cb_0x10() { RL_r8(b); }
void CPU::opcode_cb_0x0F() { RRC_r8(a); }
void CPU::opcode_cb_0x0E() { RRC_hl(); }
void CPU::opcode_cb_0x0D() { RRC_r8(l); }
void CPU::opcode_cb_0x0C() { RRC_r8(h); }
void CPU::opcode_cb_0x0B() { RRC_r8(e); }
void CPU::opcode_cb_0x0A() { RRC_r8(d); }
void CPU::opcode_cb_0x09() { RRC_r8(c); }
void CPU::opcode_cb_0x08() { RRC_r8(b); }
void CPU::opcode_cb_0x07() { RLC_r8(a); }
void CPU::opcode_cb_0x06() { RLC_hl(); }
void CPU::opcode_cb_0x05() { RLC_r8(l); }
void CPU::opcode_cb_0x04() { RLC_r8(h); }
void CPU::opcode_cb_0x03() { RLC_r8(e); }
void CPU::opcode_cb_0x02() { RLC_r8(d); }
void CPU::opcode_cb_0x01() { RLC_r8(c); }
void CPU::opcode_cb_0x00() { RLC_r8(b); }


byte CPU::RLC(byte value)
{
  byte result = (value << 1) | ((value >> 7) & 0x1);

  f.write((uint8_t)Flag::Z_ZERO, result == 0);
  f.write((uint8_t)Flag::N_SUBTRACT, false);
  f.write((uint8_t)Flag::H_HALFCARRY, false);
  f.write((uint8_t)Flag::C_CARRY, ((value >> 7) & 0x1) != 0);

  return result;
}
void CPU::RLC_r8(ByteRegister& reg)
{
  reg.set(RLC(reg.get()));
}
void CPU::RLC_hl()
{
  mmu->write(hl.get(), RLC(mmu->read(hl.get())));
}

byte CPU::RRC(byte value)
{
  byte result = ((value & 0x1) << 7) | (value >> 1);

  f.write((uint8_t)Flag::Z_ZERO, result == 0);
  f.write((uint8_t)Flag::N_SUBTRACT, false);
  f.write((uint8_t)Flag::H_HALFCARRY, false);
  f.write((uint8_t)Flag::C_CARRY, (value & 0x1) != 0);

  return result;
}
void CPU::RRC_r8(ByteRegister& reg)
{
  reg.set(RRC(reg.get()));
}
void CPU::RRC_hl()
{
  mmu->write(hl.get(), RRC(mmu->read(hl.get())));
}

byte CPU::RL(byte value)
{
  byte carry = f.read((uint8_t)Flag::C_CARRY) ? 1 : 0;
  byte result = (value << 1) | carry;

  f.write((uint8_t)Flag::Z_ZERO, result == 0);
  f.write((uint8_t)Flag::N_SUBTRACT, false);
  f.write((uint8_t)Flag::H_HALFCARRY, false);
  f.write((uint8_t)Flag::C_CARRY, ((value >> 7) & 0x1) != 0);

  return result;
}
void CPU::RL_r8(ByteRegister& reg)
{
  reg.set(RL(reg.get()));
}
void CPU::RL_hl()
{
  mmu->write(hl.get(), RL(mmu->read(hl.get())));
}

byte CPU::RR(byte value)
{
  byte carry = f.read((uint8_t)Flag::C_CARRY) ? 0x80 : 0;
  byte result = carry | (value >> 1);

  f.write((uint8_t)Flag::Z_ZERO, result == 0);
  f.write((uint8_t)Flag::N_SUBTRACT, false);
  f.write((uint8_t)Flag::H_HALFCARRY, false);
  f.write((uint8_t)Flag::C_CARRY, (value & 0x1) != 0);

  return result;
}
void CPU::RR_r8(ByteRegister& reg)
{
  reg.set(RR(reg.get()));
}
void CPU::RR_hl()
{
  mmu->write(hl.get(), RR(mmu->read(hl.get())));
}

byte CPU::SLA(byte value)
{
  byte result = value << 1;

  f.write((uint8_t)Flag::Z_ZERO, result == 0);
  f.write((uint8_t)Flag::N_SUBTRACT, false);
  f.write((uint8_t)Flag::H_HALFCARRY, false);
  f.write((uint8_t)Flag::C_CARRY, ((value >> 7) & 0x1) != 0);

  return result;
}
void CPU::SLA_r8(ByteRegister& reg)
{
  reg.set(SLA(reg.get()));
}
void CPU::SLA_hl()
{
  mmu->write(hl.get(), SLA(mmu->read(hl.get())));
}

byte CPU::SRA(byte value)
{
  byte result = (value & 0x80) | (value >> 1);

  f.write((uint8_t)Flag::Z_ZERO, result == 0);
  f.write((uint8_t)Flag::N_SUBTRACT, false);
  f.write((uint8_t)Flag::H_HALFCARRY, false);
  f.write((uint8_t)Flag::C_CARRY, ((value & 0x1) != 0));

  return result;
}
void CPU::SRA_r8(ByteRegister& reg)
{
  reg.set(SRA(reg.get()));
}
void CPU::SRA_hl()
{
  mmu->write(hl.get(), SRA(mmu->read(hl.get())));
}

byte CPU::SWAP(byte value)
{
  byte swapped = ((value << 0x0F) & 4 | (value & 0xF0) >> 4);

  f.write((uint8_t)Flag::Z_ZERO, swapped == 0);
  f.write((uint8_t)Flag::N_SUBTRACT, false);
  f.write((uint8_t)Flag::H_HALFCARRY, false);
  f.write((uint8_t)Flag::C_CARRY, false);

  return swapped;
}
void CPU::SWAP_r8(ByteRegister& reg)
{
  reg.set(SWAP(reg.get()));
}
void CPU::SWAP_hl()
{
  mmu->write(hl.get(), SWAP(mmu->read(hl.get())));
}

byte CPU::SRL(byte value)
{
  byte result = value >> 1;

  f.write((uint8_t)Flag::Z_ZERO, result == 0);
  f.write((uint8_t)Flag::N_SUBTRACT, false);
  f.write((uint8_t)Flag::H_HALFCARRY, false);
  f.write((uint8_t)Flag::C_CARRY, (value & 0x1) != 0);

  return result;
}
void CPU::SRL_r8(ByteRegister& reg)
{
  reg.set(SRL(reg.get()));
}
void CPU::SRL_hl()
{
  mmu->write(hl.get(), SRL(mmu->read(hl.get())));
}

void CPU::BIT(byte value, uint8_t bit)
{
  f.write((uint8_t)Flag::Z_ZERO, ((value >> bit) & 0x1) == 0);
  f.write((uint8_t)Flag::N_SUBTRACT, false);
  f.write((uint8_t)Flag::H_HALFCARRY, true);
}
void CPU::BIT_r8(ByteRegister& reg, uint8_t bit)
{
  BIT(reg.get(), bit);
}
void CPU::BIT_hl(uint8_t bit)
{
  BIT(mmu->read(hl.get()), bit);
}

byte CPU::RES(byte value, uint8_t bit)
{
  return (value & ~(0x1 << bit));
}
void CPU::RES_r8(ByteRegister& reg, uint8_t bit)
{
  reg.set(RES(reg.get(), bit));
}
void CPU::RES_hl(uint8_t bit)
{
  mmu->write(hl.get(), RES(mmu->read(hl.get()), bit));
}

byte CPU::SET(byte value, uint8_t bit)
{
  return value | (0x1 << bit);
}
void CPU::SET_r8(ByteRegister& reg, uint8_t bit)
{
  reg.set(SET(reg.get(), bit));
}
void CPU::SET_hl(uint8_t bit)
{
  mmu->write(hl.get(), SET(mmu->read(hl.get()), bit));
}
