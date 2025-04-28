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

/* INC */
void CPU::opcode_0x04() { INC_r8(b); }
void CPU::opcode_0x14() { INC_r8(d); }
void CPU::opcode_0x24() { INC_r8(h); }
void CPU::opcode_0x34()
{
  byte lo = uint8_t(hl.get() & 0xFF);
  bool half_carry = ((lo & 0x0F) + 1) > 0x0F;

  hl.increment();

  flags.zf = (hl.get() == 0);
  flags.nf = false;
  flags.hf = half_carry;
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
  int8_t e = static_cast<int8_t>(mmu->read(pc.get()));
  pc.increment();
  word res = sp.get() + e;
  hl.set(res);

  // Flag logic
  byte lo = uint8_t(sp.get() & 0xFF);
  byte ue = uint8_t(e);

  bool half_carry = ((lo & 0x0F) + (ue & 0x0F)) > 0x0F;
  bool carry = (uint16_t(lo) + uint16_t(ue)) > 0xFF;

  flags.zf = false;
  flags.nf = false;
  flags.hf = half_carry;
  flags.cf = carry;
}
void CPU::opcode_0xF9() {
  sp.set(hl.get());
}


/* JP */
void CPU::opcode_0xC3() { JP_n16(); }


/* JR */
void CPU::opcode_0x20() { JR_cc_e(!flags.zf); }
void CPU::opcode_0x30() { JR_cc_e(!flags.cf); }

void CPU::opcode_0x18() { JR_cc_e(); }
void CPU::opcode_0x28() { JR_cc_e(flags.zf); }
void CPU::opcode_0x38() { JR_cc_e(flags.cf); }

/* CALL */
void CPU::opcode_0xCD() { CALL_nn(); }

void CPU::opcode_0xCC() { CALL_nn(flags.zf); }
void CPU::opcode_0xDC() { CALL_nn(flags.cf); }

void CPU::opcode_0xC4() { CALL_nn(!flags.zf); }
void CPU::opcode_0xD4() { CALL_nn(!flags.cf); }


/* RET */
void CPU::opcode_0xC9() { RET_cc(); }


/* POP */
void CPU::opcode_0xC1() { stack_pop(bc); }
void CPU::opcode_0xD1() { stack_pop(de); }
void CPU::opcode_0xE1() { stack_pop(hl); }
void CPU::opcode_0xF1()
{
  byte popped_lsb = mmu->read(sp.get());
  // TODO:
  // stack_pop(af);

  flags.zf = ((popped_lsb & 0x10) != 0);
  flags.nf = ((popped_lsb & 0x20) != 0);
  flags.hf = ((popped_lsb & 0x40) != 0);
  flags.cf = ((popped_lsb & 0x80) != 0);
}


/* PUSH */
void CPU::opcode_0xC5() { stack_push(bc); }
void CPU::opcode_0xD5() { stack_push(de); }
void CPU::opcode_0xE5() { stack_push(hl); }
void CPU::opcode_0xF5()
{
  sp.decrement();
  mmu->write(sp.get(), a.get());

  sp.decrement();
  byte flag = flags.zf << 7 | flags.nf << 6 | flags.hf << 5 | flags.cf << 4;
  mmu->write(sp.get(), flag);

  word value = (a.get() << 8) | flag;

  LOG("FLAGS: 0x%04X, 0x%04X, 0x%04X, 0x%04X", flags.zf, flags.nf, flags.hf, flags.cf);
  LOG("PUSH: 0x%04X, 0x%04X, 0x%04X", value, a.get(), flag);
}


/* AND */
void CPU::opcode_0xA0() { AND_r8(b); }
void CPU::opcode_0xA1() { AND_r8(c); }
void CPU::opcode_0xA2() { AND_r8(d); }
void CPU::opcode_0xA3() { AND_r8(e); }
void CPU::opcode_0xA4() { AND_r8(h); }
void CPU::opcode_0xA5() { AND_r8(l); }
void CPU::opcode_0xA7() { AND_r8(a); }
void CPU::opcode_0xA6() { AND_r16(hl); }
void CPU::opcode_0xE6() { AND_r16(pc); }


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
void CPU::opcode_0xB1() {
  byte bc_msb = bc.get() >> 8;
  byte bc_lsb = bc.get() & 0x00FF;

  /* NEEDS FIX */
  b.set(bc_msb);
  c.set(bc_lsb);

  OR_r8(c);
}
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



/* ======================================== */


/* INC */
void CPU::INC_r8(ByteRegister& reg)
{
  byte lo = uint8_t(reg.get() & 0xFF);
  bool half_carry = ((lo & 0x0F) + 1) > 0x0F;

  reg.increment();

  flags.zf = (reg.get() == 0);
  flags.nf = false;
  flags.hf = half_carry;
}

/* LD */
void CPU::LD_r8_r8(ByteRegister& reg1, ByteRegister& reg2)
{
  reg1.set(reg2.get());
}

void CPU::LD_r8_n8(ByteRegister& reg)
{
  byte value = mmu->read(pc.get());
  pc.increment();
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
  // reg16.increment();
}

void CPU::LD_addr16_n8(RegisterPair& reg)
{
  byte value = mmu->read(pc.get());
  pc.increment();
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
void CPU::JP_n16()
{
  word addr = mmu->read(pc.get());
  pc.increment();
  addr |= mmu->read(pc.get()) << 8;
  pc.increment();

  pc.set(addr);
}

/* JR */
void CPU::JR_cc_e(bool conditional)
{
  int8_t e = static_cast<int8_t>(mmu->read(pc.get()));
  pc.increment();

  if (conditional) {
    cond_cycles = true;
    word res = pc.get() + e;
    pc.set(res);
  }
}


/* CALL */
void CPU::CALL_nn(bool conditional)
{
  if (conditional) {
    cond_cycles = true;
    byte lsb = mmu->read(pc.get());
    pc.increment();
    byte msb = mmu->read(pc.get());
    pc.increment();

    stack_push(pc);

    word nn = (msb << 8) | lsb;
    pc.set(nn);
  }
}


/* RET */
void CPU::RET_cc(bool condtiional)
{
  stack_pop(pc);
}


/* POP */
// void CPU::POP_r16(WordRegister& reg)
// {
//   byte lsb = mmu->read(sp.get());
//   sp.increment();
//   byte msb = mmu->read(sp.get());
//   sp.increment();

//   word value = (msb << 8) | lsb;
//   LOG("POP: 0x%04X", value);
//   reg.set(value);
// }


// /* PUSH */
// void CPU::PUSH_r16(WordRegister& reg)
// {
//   sp.decrement();
//   mmu->write(sp.get(), reg.get() >> 8);
//   sp.decrement();
//   mmu->write(sp.get(), reg.get() & 0xFF);

//   LOG("FLAGS: 0x%04X, 0x%04X, 0x%04X, 0x%04X", flags.zf, flags.nf, flags.hf, flags.cf);
//   LOG("PUSH: 0x%04X", reg.get());
// }


/* AND */
void CPU::AND(byte value)
{
  byte result = a.get() & value;
  a.set(result);

  flags.zf = (result == 0);
  flags.nf = false;
  flags.hf = true;
  flags.cf = false;
}
void CPU::AND_r8(ByteRegister& reg)
{
  AND(reg.get());
}
void CPU::AND_r16(RegisterPair& reg)
{
  AND(mmu->read(reg.get()));
}


/* TEMPORARY */
void CPU::AND_r16(WordRegister& reg)
{
  AND(mmu->read(reg.get()));
}



/* DEC */
void CPU::DEC_r8(ByteRegister& reg)
{
  byte lo = uint8_t(reg.get() & 0xFF);
  bool half_carry = ((lo & 0x0F) + 1) > 0x0F;

  reg.decrement();

  flags.zf = (reg.get() == 0);
  flags.nf = true;
  flags.hf = half_carry;
}
void CPU::DEC_hl()
{
  byte lo = uint8_t(hl.get() & 0xFF);
  bool half_carry = ((lo & 0x0F) + 1) > 0x0F;

  hl.decrement();

  flags.zf = (hl.get() == 0);
  flags.nf = true;
  flags.hf = half_carry;
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
  byte reg = a.get();
  byte result = reg | value;
  a.set(result);

  flags.zf = (result == 0);
  flags.nf = false;
  flags.hf = false;
  flags.cf = false;

  LOG("OR: 0x%02X, 0x%02X", reg, value);
  LOG("FLAGS: 0x%04X, 0x%04X, 0x%04X, 0x%04X", flags.zf, flags.nf, flags.hf, flags.cf);

}
void CPU::OR_r8(ByteRegister& reg)
{
  OR(reg.get());
}
void CPU::OR_n8()
{
  byte value = mmu->read(pc.get());
  OR(value);
}
void CPU::OR_r16(RegisterPair& reg)
{
  byte value = mmu->read(reg.get());
  OR(value);
}


/* CP */
void CPU::CP(byte value)
{
  byte result = a.get() - value;

  flags.zf = (result == 0);
  flags.nf = true;
  flags.hf = (a.get() & 0x0F) < (value & 0x0F);
  flags.cf = a.get() < value;

  LOG("CP: 0x%02X, 0x%02X, 0x%02X", a.get(), result, value);
  LOG("FLAGS: 0x%04X, 0x%04X, 0x%04X, 0x%04X", flags.zf, flags.nf, flags.hf, flags.cf);
}
void CPU::CP_r8(ByteRegister& reg)
{
  CP(reg.get());
}
void CPU::CP_n8()
{
  byte value = mmu->read(pc.get());
  CP(value);
}
void CPU::CP_r16(RegisterPair& reg)
{
  byte value = mmu->read(reg.get());
  CP(value);
}
