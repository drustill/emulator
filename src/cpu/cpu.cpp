#include "cpu.h"

/**
 * CPU constructor
 */
CPU::CPU(Memory* mem) : memory(mem)
{
  registers.pc = 0x100;

  // http://www.codeslinger.co.uk/pages/projects/gameboy/hardware.html
  // registers.sp = 0xFFFE;
}

/**
 * LD: Load data
 */
void CPU::LD(const uint8_t &src, uint8_t &dst)
{
  r1 = r2
}

/**
 * ADD: Add data
 */
void CPU::ADD(uint8_t value)
{
  uint16_t result = registers.a + value;
  flags.z = ((result & 0xFF) == 0);
  flags.n = false;
  flags.h = (registers.a & 0xF + value & 0xF) > 0xF;
  flags.c = result > 0xFF;

  registers.a = result & 0xFF; // Wrap back to 8 bit
}

/**
 * SUB: Subtract data
 */
void CPU::SUB(uint8_t value)
{
  uint16_t result = registers.a - value;
  flags.z = ((result & 0xFF) == 0);
  flags.n = true;
  flags.h = (registers.a & 0xF + value & 0xF) > 0xF;
  flags.c = result > 0xFF;

  registers.a = result & 0xFF; // Wrap back to 8 bit
}

/**
 * decode_reg: Map opcode to register
 */
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

/**
 * fetch_byte: Fetch a byte from memory
 */
uint8_t CPU::fetch_byte()
{
  return memory->read(registers.pc++)
}

int CPU::execute_next_opcode()
{
  int res = 0;
  uint8_t opcode = fetch_byte();
  registers.pc++;
  res = execute(opcode);
  return res;
}

/**
 * execute: Execute an instruction
 * Returns the duration in number of cycles
 */
int CPU::execute(uint8_t opcode)
{
  uint8_t op_top (opcode & 0xC0) >> 6;
  switch (op_top)
  {
    case 0x00: {
      // NOP
      return 4;
    }

    case 0x01: {
      // LD
      uint8_t dst = (opcode & 0x38) >> 3;
      uint8_t src = (opcode & 0x07);

      if (dst == 6 && src == 6) {
        std::cerr << "Loading HL from HL" << "\n";
        return 0;
      } else if (dst == 6) {
        // Something with HL
        return 8;
      } else if (src == 6) {
        // decode_reg(dst) == Read HL
        return 8;
      } else {
        decode_reg(dst) = decode_reg(src);
        return 4;
      }
      break;
    }

    case 0x02: {
      // ADD, SUB
      uint8_t dst = opcode & 0x07;
      ADD(decode_reg(dst));
      return 4;
    }

    default: {
      std::cerr << "Unimplemented opcode: " << std::hex << (int)opcode << "\n";
      return 0;
    }
  }
}
