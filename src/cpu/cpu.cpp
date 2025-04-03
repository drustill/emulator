#include "cpu.h"

CPU::CPU()
{

}

void CPU::LD(const uint8_t &src, uint8_t &dst)
{
  r1 = r2
}

void CPU::ADD(uint8_t value)
{
  uint16_t result = registers.a + value;
  flags.z = ((result & 0xFF) == 0);
  flags.n = false;
  flags.h = (registers.a & 0xF + value & 0xF) > 0xF;
  flags.c = result > 0xFF;

  registers.a = result & 0xFF; // Wrap back to 8 bit
}

void CPU::execute(uint8_t opcode)
{
  switch opcode
  {
    case 0x00:
      break;
    case 0x41:
      LD(registers.b, registers.c)
    case 0x80:
      ADD(registers.b);
      break;
    case 0xC6:
    case 0x86:
      // How to read?
      // ADD(registers.hl);
      // break;
  }
}
