#include <iostream>
#include <format>

#include "../logger.h"
#include "../optable.h"
#include "cpu.h"

int TrueCycleTable[256] = {
  1, 3, 2, 2, 1, 1, 2, 1, 5, 2, 2, 2, 1, 1, 2, 1,
  1, 3, 2, 2, 1, 1, 2, 1, 3, 2, 2, 2, 1, 1, 2, 1,
  3, 3, 2, 2, 1, 1, 2, 1, 3, 2, 2, 2, 1, 1, 2, 1,
  3, 3, 2, 2, 3, 3, 3, 1, 3, 2, 2, 2, 1, 1, 2, 1,
  1, 1, 1, 1, 1, 1, 2, 1, 1, 1, 1, 1, 1, 1, 2, 1,
  1, 1, 1, 1, 1, 1, 2, 1, 1, 1, 1, 1, 1, 1, 2, 1,
  1, 1, 1, 1, 1, 1, 2, 1, 1, 1, 1, 1, 1, 1, 2, 1,
  2, 2, 2, 2, 2, 2, 1, 2, 1, 1, 1, 1, 1, 1, 2, 1,
  1, 1, 1, 1, 1, 1, 2, 1, 1, 1, 1, 1, 1, 1, 2, 1,
  1, 1, 1, 1, 1, 1, 2, 1, 1, 1, 1, 1, 1, 1, 2, 1,
  1, 1, 1, 1, 1, 1, 2, 1, 1, 1, 1, 1, 1, 1, 2, 1,
  1, 1, 1, 1, 1, 1, 2, 1, 1, 1, 1, 1, 1, 1, 2, 1,
  5, 3, 4, 4, 6, 4, 2, 4, 5, 4, 4, 0, 6, 6, 2, 4,
  5, 3, 4, 0, 6, 4, 2, 4, 5, 4, 4, 0, 6, 0, 2, 4,
  3, 3, 2, 0, 0, 4, 2, 4, 4, 1, 4, 0, 0, 0, 2, 4,
  3, 3, 2, 1, 0, 4, 2, 4, 3, 2, 4, 1, 0, 0, 2, 4
};

int FalseCycleTable[256] = {
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
  word addr = pc.get();
  byte opcode = read_pc();

  if (opcode == 0xCB) {
    byte cb = read_pc();
    return execute_cb(cb, addr)
  }

  return execute(opcode, addr);
}

/**
 * read_pc: get the next byte from the program counter
 */
byte CPU::read_pc()
{
  word address = pc.get();
  pc.increment();

  return mmu->read(address);
}

/**
 * read_pc_word: get the next word from the program counter
 */
word CPU::read_pc_word()
{
  byte lo = read_pc();
  byte hi = read_pc();

  return (hi << 8) | lo;
}

/**
 * read_pc_signed: get the next byte from the program counter as a signed int
 */
int8_t CPU::read_pc_signed()
{
  return static_cast<int8_t>(read_pc());
}



int CPU::execute(byte opcode, word address)
{
  LOG("[0x%04X]  %s (0x%x)", address, opcode_metadata[opcode].c_str(), opcode);

  cond_cycles = false;

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
    case 0xF0: opcode_0xF0(); break; case 0x00: opcode_0x00(); break; case 0xC3: opcode_0xC3(); break; case 0x01: opcode_0x01(); break;
    case 0x11: opcode_0x11(); break; case 0x21: opcode_0x21(); break; case 0x31: opcode_0x31(); break; case 0x08: opcode_0x08(); break;
    case 0xF8: opcode_0xF8(); break; case 0xF9: opcode_0xF9(); break; case 0x0A: opcode_0x0A(); break; case 0x1A: opcode_0x1A(); break;
    case 0x2A: opcode_0x2A(); break; case 0x3A: opcode_0x3A(); break; case 0x04: opcode_0x04(); break; case 0x14: opcode_0x14(); break;
    case 0x24: opcode_0x24(); break; case 0x34: opcode_0x34(); break; case 0x0C: opcode_0x0C(); break; case 0x1C: opcode_0x1C(); break;
    case 0x2C: opcode_0x2C(); break; case 0x3C: opcode_0x3C(); break; case 0x20: opcode_0x20(); break; case 0x30: opcode_0x30(); break;
    case 0xF3: opcode_0xF3(); break; case 0xFB: opcode_0xFB(); break; case 0xC4: opcode_0xC4(); break; case 0xD4: opcode_0xD4(); break;
    case 0xCC: opcode_0xCC(); break; case 0xDC: opcode_0xDC(); break; case 0xCD: opcode_0xCD(); break; case 0x18: opcode_0x18(); break;
    case 0x28: opcode_0x28(); break; case 0x38: opcode_0x38(); break; case 0xC9: opcode_0xC9(); break; case 0xC1: opcode_0xC1(); break;
    case 0xD1: opcode_0xD1(); break; case 0xE1: opcode_0xE1(); break; case 0xF1: opcode_0xF1(); break; case 0xC5: opcode_0xC5(); break;
    case 0xD5: opcode_0xD5(); break; case 0xE5: opcode_0xE5(); break; case 0xF5: opcode_0xF5(); break; case 0xA6: opcode_0xA6(); break;
    case 0xE6: opcode_0xE6(); break; case 0xA0: opcode_0xA0(); break; case 0xA1: opcode_0xA1(); break; case 0xA2: opcode_0xA2(); break;
    case 0xA3: opcode_0xA3(); break; case 0xA4: opcode_0xA4(); break; case 0xA5: opcode_0xA5(); break; case 0xA7: opcode_0xA7(); break;
    case 0x05: opcode_0x05(); break; case 0x15: opcode_0x15(); break; case 0x25: opcode_0x25(); break; case 0x35: opcode_0x35(); break;
    case 0x0D: opcode_0x0D(); break; case 0x1D: opcode_0x1D(); break; case 0x2D: opcode_0x2D(); break; case 0x3D: opcode_0x3D(); break;
    case 0x33: opcode_0x33(); break; case 0x23: opcode_0x23(); break; case 0x13: opcode_0x13(); break; case 0x03: opcode_0x03(); break;
    case 0x3B: opcode_0x3B(); break; case 0x2B: opcode_0x2B(); break; case 0x1B: opcode_0x1B(); break; case 0x0B: opcode_0x0B(); break;
    case 0xB7: opcode_0xB7(); break; case 0xB5: opcode_0xB5(); break; case 0xB4: opcode_0xB4(); break; case 0xB3: opcode_0xB3(); break;
    case 0xB2: opcode_0xB2(); break; case 0xB1: opcode_0xB1(); break; case 0xB0: opcode_0xB0(); break; case 0xF6: opcode_0xF6(); break;
    case 0xB6: opcode_0xB6(); break; case 0xBF: opcode_0xBF(); break; case 0xBE: opcode_0xBE(); break; case 0xBD: opcode_0xBD(); break;
    case 0xBC: opcode_0xBC(); break; case 0xBB: opcode_0xBB(); break; case 0xBA: opcode_0xBA(); break; case 0xB9: opcode_0xB9(); break;
    case 0xB8: opcode_0xB8(); break; case 0xFE: opcode_0xFE(); break; case 0xC8: opcode_0xC8(); break; case 0xD8: opcode_0xD8(); break;
    case 0xAF: opcode_0xAF(); break; case 0xAE: opcode_0xAE(); break; case 0xAD: opcode_0xAD(); break; case 0xAC: opcode_0xAC(); break;
    case 0xAB: opcode_0xAB(); break; case 0xAA: opcode_0xAA(); break; case 0xA9: opcode_0xA9(); break; case 0xA8: opcode_0xA8(); break;
    case 0xEE: opcode_0xEE(); break; case 0x87: opcode_0x87(); break; case 0x86: opcode_0x86(); break; case 0x85: opcode_0x85(); break;
    case 0x84: opcode_0x84(); break; case 0x83: opcode_0x83(); break; case 0x82: opcode_0x82(); break; case 0x81: opcode_0x81(); break;
    case 0x80: opcode_0x80(); break; case 0xC6: opcode_0xC6(); break; case 0x97: opcode_0x97(); break; case 0x96: opcode_0x96(); break;
    case 0x95: opcode_0x95(); break; case 0x94: opcode_0x94(); break; case 0x93: opcode_0x93(); break; case 0x92: opcode_0x92(); break;
    case 0x91: opcode_0x91(); break; case 0x90: opcode_0x90(); break; case 0xD6: opcode_0xD6(); break; case 0x8F: opcode_0x8F(); break;
    case 0x8D: opcode_0x8D(); break; case 0x8C: opcode_0x8C(); break; case 0x8B: opcode_0x8B(); break; case 0x8A: opcode_0x8A(); break;
    case 0x89: opcode_0x89(); break; case 0x88: opcode_0x88(); break; case 0xCE: opcode_0xCE(); break; case 0x8E: opcode_0x8E(); break;
    case 0x9F: opcode_0x9F(); break; case 0x9D: opcode_0x9D(); break; case 0x9C: opcode_0x9C(); break; case 0x9B: opcode_0x9B(); break;
    case 0x9A: opcode_0x9A(); break; case 0x99: opcode_0x99(); break; case 0x98: opcode_0x98(); break; case 0xDE: opcode_0xDE(); break;
    case 0x9E: opcode_0x9E(); break;

    default:
      std::cerr << "Unknown opcode: 0x" << std::hex << (int)opcode << std::dec << std::endl;
      exit(1);
      // return 69905;
      // break;
  }

  return cond_cycles ? TrueCycleTable[opcode] : FalseCycleTable[opcode];
}

int CPU::execute_cb(byte opcode, word address)
{
  LOG("[0x%04X]  %s (CB 0x%x)", address, opcode_metadata[opcode].c_str(), opcode);

  switch (opcode) {

  }

  return CallbackCycleTable[opcode];
}
