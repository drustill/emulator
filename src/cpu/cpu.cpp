#include "cpu.h"

CPU::CPU(Memory* mem) : memory(mem)
{
  registers.pc = 0x0100;
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

uint8_t& CPU::decode_reg(uint8_t code)
{
  switch (code)
  {
    case 0: return registers.b;
    case 1: return registers.c;
    case 2: return registers.d;
    case 3: return registers.e;
    case 4: return registers.h;
    case 5: return registers.l;
    case 7: return registers.a;
    default:
      throw std::invalid_argument("Invalid register code. Probably HL");
  }
}

void CPU::execute(uint8_t opcode)
{
  uint8_t op_top (opcode & 0xC0) >> 6;
  switch (op_top)
  {
    case 0x00: {
      // NOP
      break;
    }

    case 0x01: {
      // LD
      uint8_t dst = (opcode & 0x38) >> 3;
      uint8_t src = (opcode & 0x07);

      if (dst == 6 && src == 6) {
        break;
      } else if (dst == 6) {
        // Something with HL
      } else if (src == 6) {
        // decode_reg(dst) == Read HL
      } else {
        decode_reg(dst) = decode_reg(src);
      }
      break;
    }

    case 0x02: {
      // ADD, SUB
      uint8_t dst = opcode & 0x07;
      ADD(decode_reg(dst));
      break;
    }

  }
}
