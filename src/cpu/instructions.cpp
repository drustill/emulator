#include "cpu.h"

/**
 * r8: ByteRegister
 * r16: WordRegister
 * n8: 8-bit immediate value
 * nn16: 16-bit immediate value
 */

/* LD */
void CPU::LD_r8_r8(ByteRegister& reg1, ByteRegister& reg2)
{
  reg1.set(reg2.get());
}

void CPU::LD_r8_n8(ByteRegister& reg, byte value)
{
  reg.set(value);
}
