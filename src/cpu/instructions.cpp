#include "cpu.h"

/**
 * r8: ByteRegister
 * r16: WordRegister
 * n8: 8-bit immediate value
 * nn16: 16-bit immediate value
 */


/* LD opcode mappings */
void CPU::opcode_0x40() { LD_r8_r8(b, b); }
void CPU::opcode_0x41() { LD_r8_r8(b, c); }
void CPU::opcode_0x42() { LD_r8_r8(b, d); }
void CPU::opcode_0x43() { LD_r8_r8(b, e); }
void CPU::opcode_0x44() { LD_r8_r8(b, h); }
void CPU::opcode_0x45() { LD_r8_r8(b, l); }
void CPU::opcode_0x46() { LD_r8_from_hl(b); }
void CPU::opcode_0x47() { LD_r8_r8(b, a); }

void CPU::opcode_0x48() { LD_r8_r8(c, b); }
void CPU::opcode_0x49() { LD_r8_r8(c, c); }
void CPU::opcode_0x4A() { LD_r8_r8(c, d); }
void CPU::opcode_0x4B() { LD_r8_r8(c, e); }
void CPU::opcode_0x4C() { LD_r8_r8(c, h); }
void CPU::opcode_0x4D() { LD_r8_r8(c, l); }
void CPU::opcode_0x4E() { LD_r8_from_hl(c); }
void CPU::opcode_0x4F() { LD_r8_r8(c, a); }

void CPU::opcode_0x50() { LD_r8_r8(d, b); }
void CPU::opcode_0x51() { LD_r8_r8(d, c); }
void CPU::opcode_0x52() { LD_r8_r8(d, d); }
void CPU::opcode_0x53() { LD_r8_r8(d, e); }
void CPU::opcode_0x54() { LD_r8_r8(d, h); }
void CPU::opcode_0x55() { LD_r8_r8(d, l); }
void CPU::opcode_0x56() { LD_r8_from_hl(d); }
void CPU::opcode_0x57() { LD_r8_r8(d, a); }

void CPU::opcode_0x58() { LD_r8_r8(e, b); }
void CPU::opcode_0x59() { LD_r8_r8(e, c); }
void CPU::opcode_0x5A() { LD_r8_r8(e, d); }
void CPU::opcode_0x5B() { LD_r8_r8(e, e); }
void CPU::opcode_0x5C() { LD_r8_r8(e, h); }
void CPU::opcode_0x5D() { LD_r8_r8(e, l); }
void CPU::opcode_0x6E() { LD_r8_from_hl(e); }
void CPU::opcode_0x5F() { LD_r8_r8(e, a); }

void CPU::opcode_0x60() { LD_r8_r8(h, b); }
void CPU::opcode_0x61() { LD_r8_r8(h, c); }
void CPU::opcode_0x62() { LD_r8_r8(h, d); }
void CPU::opcode_0x63() { LD_r8_r8(h, e); }
void CPU::opcode_0x64() { LD_r8_r8(h, h); }
void CPU::opcode_0x65() { LD_r8_r8(h, l); }
void CPU::opcode_0x66() { LD_hl_from_r8(h); }
void CPU::opcode_0x67() { LD_r8_r8(h, a); }

void CPU::opcode_0x68() { LD_r8_r8(l, b); }
void CPU::opcode_0x69() { LD_r8_r8(l, c); }
void CPU::opcode_0x6A() { LD_r8_r8(l, d); }
void CPU::opcode_0x6B() { LD_r8_r8(l, e); }
void CPU::opcode_0x6C() { LD_r8_r8(l, h); }
void CPU::opcode_0x6D() { LD_r8_r8(l, l); }
void CPU::opcode_0x6E() { LD_r8_from_hl(l); }
void CPU::opcode_0x6F() { LD_r8_r8(l, a); }

/* LD */
void CPU::LD_r8_r8(ByteRegister& reg1, ByteRegister& reg2)
{
  reg1.set(reg2.get());
}

void CPU::LD_hl_from_r8(ByteRegister& reg)
{
  word hl = hl.get();
  mmu->write(hl, reg.get());
}

void CPU::LD_r8_from_hl(ByteRegister& reg)
{
  word hl = hl.get();
  reg.set(mmu->read(hl));
}

void CPU::LD_r8_n8(ByteRegister& reg, byte value)
{
  reg.set(value);
}

void CPU::LD_r16_nn16(WordRegister& reg, word value)
{
  reg.set(value);
}
