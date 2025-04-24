#include <iostream>
#include "cpu.h"

int CycleTable[256] = {
  1, 3, 2, 2, 1, 1, 2, 1, 5, 2, 2, 2, 1, 1, 2, 1,
  1, 3, 2, 2, 1, 1, 2, 1, 3, 2, 2, 2, 1, 1, 2, 1,
  2, 3, 2, 2, 1, 1, 2, 1, 2, 2, 2, 2, 1, 1, 2, 1,
  2, 3, 2, 2, 3, 3, 3, 1, 2, 2, 2, 2, 1, 1, 2, 1,
  1, 1, 1, 1, 1, 1, 2, 1, 1, 1, 1, 1, 1, 1, 2, 1,
  1, 1, 1, 1, 1, 1, 2, 1, 1, 1, 1, 1, 1, 1, 2, 1,
  1, 1, 1, 1, 1, 1, 2, 1, 1, 1, 1, 1, 1, 1, 2, 1,
  2, 2, 2, 2, 2, 2, 1, 2, 1, 1, 1, 1, 1, 1, 2, 1,
  1, 1, 1, 1, 1, 1, 2, 1, 1, 1, 1, 1, 1, 1, 2, 1,
  1, 1, 1, 1, 1, 1, 2, 1, 1, 1, 1, 1, 1, 1, 2, 1,
  1, 1, 1, 1, 1, 1, 2, 1, 1, 1, 1, 1, 1, 1, 2, 1,
  1, 1, 1, 1, 1, 1, 2, 1, 1, 1, 1, 1, 1, 1, 2, 1,
  2, 3, 3, 4, 3, 4, 2, 4, 2, 4, 3, 0, 3, 6, 2, 4,
  2, 3, 3, 0, 3, 4, 2, 4, 2, 4, 3, 0, 3, 0, 2, 4,
  3, 3, 2, 0, 0, 4, 2, 4, 4, 1, 4, 0, 0, 0, 2, 4,
  3, 3, 2, 1, 0, 4, 2, 4, 3, 2, 4, 1, 0, 0, 2, 4
};

/**
 * CPU constructor
 * - http://www.codeslinger.co.uk/pages/projects/gameboy/hardware.html
 */
CPU::CPU(MMU* mmu) : mmu(mmu)
{
  pc.set(0x100);
}

/**
 * tick: Fetch and execute the next opcode
 * Returns the number of cycles taken
 */
int CPU::tick()
{
  byte opcode = mmu->read(pc.get());
  pc.increment();
  return execute(opcode);
}

int CPU::execute(byte opcode)
{
  std::cout << "Executing opcode: 0x" << std::hex << (int)opcode << std::dec << std::endl;

  switch (opcode) {
    case 0x02: opcode_0x02(); break; case 0x12: opcode_0x12(); break; case 0x22: opcode_0x22(); break; case 0x32: opcode_0x32(); break;
    case 0x06: opcode_0x06(); break; case 0x16: opcode_0x16(); break; case 0x26: opcode_0x26(); break; case 0x36: opcode_0x36(); break;
    case 0x0E: opcode_0x0E(); break; case 0x1E: opcode_0x1E(); break; case 0x2E: opcode_0x2E(); break; case 0x3E: opcode_0x3E(); break;
    case 0x40: opcode_0x40(); break; case 0x41: opcode_0x41(); break; case 0x42: opcode_0x42(); break; case 0x43: opcode_0x43(); break;
    case 0x44: opcode_0x44(); break; case 0x45: opcode_0x45(); break; case 0x46: opcode_0x46(); break; case 0x47: opcode_0x47(); break;
    case 0x48: opcode_0x48(); break; case 0x49: opcode_0x49(); break; case 0x4A: opcode_0x4A(); break; case 0x4B: opcode_0x4B(); break;
    case 0x4C: opcode_0x4C(); break; case 0x4D: opcode_0x4D(); break; case 0x4E: opcode_0x4E(); break; case 0x4F: opcode_0x4F(); break;
    case 0x50: opcode_0x50(); break; case 0x51: opcode_0x51(); break; case 0x52: opcode_0x52(); break; case 0x53: opcode_0x53(); break;
    case 0x54: opcode_0x54(); break; case 0x55: opcode_0x55(); break; case 0x56: opcode_0x56(); break; case 0x57: opcode_0x57(); break;
    case 0x58: opcode_0x58(); break; case 0x59: opcode_0x59(); break; case 0x5A: opcode_0x5A(); break; case 0x5B: opcode_0x5B(); break;
    case 0x5C: opcode_0x5C(); break; case 0x5D: opcode_0x5D(); break; case 0x5E: opcode_0x5E(); break; case 0x5F: opcode_0x5F(); break;
    case 0x60: opcode_0x60(); break; case 0x61: opcode_0x61(); break; case 0x62: opcode_0x62(); break; case 0x63: opcode_0x63(); break;
    case 0x64: opcode_0x64(); break; case 0x65: opcode_0x65(); break; case 0x66: opcode_0x66(); break; case 0x67: opcode_0x67(); break;
    case 0x68: opcode_0x68(); break; case 0x69: opcode_0x69(); break; case 0x6A: opcode_0x6A(); break; case 0x6B: opcode_0x6B(); break;
    case 0x6C: opcode_0x6C(); break; case 0x6D: opcode_0x6D(); break; case 0x6E: opcode_0x6E(); break; case 0x6F: opcode_0x6F(); break;
    case 0x70: opcode_0x70(); break; case 0x71: opcode_0x71(); break; case 0x72: opcode_0x72(); break; case 0x73: opcode_0x73(); break;
    case 0x74: opcode_0x74(); break; case 0x75: opcode_0x75(); break; case 0x77: opcode_0x77(); break; case 0x78: opcode_0x78(); break;
    case 0x79: opcode_0x79(); break; case 0x7A: opcode_0x7A(); break; case 0x7B: opcode_0x7B(); break; case 0x7C: opcode_0x7C(); break;
    case 0x7D: opcode_0x7D(); break; case 0x7E: opcode_0x7E(); break; case 0x7F: opcode_0x7F(); break; case 0xE2: opcode_0xE2(); break;
    case 0xF2: opcode_0xF2(); break; case 0xEA: opcode_0xEA(); break; case 0xFA: opcode_0xFA(); break; case 0xE0: opcode_0xE0(); break;
    case 0xF0: opcode_0xF0(); break;

    default:
      std::cerr << "Unknown opcode: 0x" << std::hex << (int)opcode << std::dec << std::endl;
      return 0;
  }

  return CycleTable[opcode];
}
