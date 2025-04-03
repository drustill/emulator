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

void CPU::SUB(uint8_t value)
{
  uint16_t result = registers.a - value;
  flags.z = ((result & 0xFF) == 0);
  flags.n = true;
  flags.h = (registers.a & 0xF + value & 0xF) > 0xF;
  flags.c = result > 0xFF;

  registers.a = result & 0xFF; // Wrap back to 8 bit
}

void CPU::decode_reg(uint8_t opcode)
{
  uint16_t op_top (opcode & 0xC0) >> 6;
  uint16_t op_mid (opcode & 0x38) >> 3;
  uint16_t op_end (opcode & 0x07);


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
    case 0x81:
      ADD(registers.c);
      break;
    case 0x82:
      ADD(registers.d);
      break;
    case 0x83:
      ADD(registers.e);
      break;
    case 0x84:
      ADD(registers.h);
      break;
    case 0x85:
      ADD(registers.l);
      break;
    case 0x86:
      ADD(registers.hl)
      break;
    case 0x87:
      ADD(registers.a);
      break;

    case 0xC6:
      // How to read?

    case 0x90:
      SUB(registers.b);
      break;
    case 0xD6:
      // How to read?

  }
}
