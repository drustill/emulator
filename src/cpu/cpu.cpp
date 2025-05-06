#include <iostream>
#include <format>

#include "cpu.h"
#include "log.h"
#include "optable.h"

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

int CallbackCycleTable[256] = {
  2, 2, 2, 2, 2, 2, 4, 2, 2, 2, 2, 2, 2, 2, 4, 2,
  2, 2, 2, 2, 2, 2, 4, 2, 2, 2, 2, 2, 2, 2, 4, 2,
  2, 2, 2, 2, 2, 2, 4, 2, 2, 2, 2, 2, 2, 2, 4, 2,
  2, 2, 2, 2, 2, 2, 4, 2, 2, 2, 2, 2, 2, 2, 4, 2,
  2, 2, 2, 2, 2, 2, 3, 2, 2, 2, 2, 2, 2, 2, 3, 2,
  2, 2, 2, 2, 2, 2, 3, 2, 2, 2, 2, 2, 2, 2, 3, 2,
  2, 2, 2, 2, 2, 2, 3, 2, 2, 2, 2, 2, 2, 2, 3, 2,
  2, 2, 2, 2, 2, 2, 3, 2, 2, 2, 2, 2, 2, 2, 3, 2,
  2, 2, 2, 2, 2, 2, 4, 2, 2, 2, 2, 2, 2, 2, 4, 2,
  2, 2, 2, 2, 2, 2, 4, 2, 2, 2, 2, 2, 2, 2, 4, 2,
  2, 2, 2, 2, 2, 2, 4, 2, 2, 2, 2, 2, 2, 2, 4, 2,
  2, 2, 2, 2, 2, 2, 4, 2, 2, 2, 2, 2, 2, 2, 4, 2,
  2, 2, 2, 2, 2, 2, 4, 2, 2, 2, 2, 2, 2, 2, 4, 2,
  2, 2, 2, 2, 2, 2, 4, 2, 2, 2, 2, 2, 2, 2, 4, 2,
  2, 2, 2, 2, 2, 2, 4, 2, 2, 2, 2, 2, 2, 2, 4, 2,
  2, 2, 2, 2, 2, 2, 4, 2, 2, 2, 2, 2, 2, 2, 4, 2
};

/**
 * CPU constructor
 * - http://www.codeslinger.co.uk/pages/projects/gameboy/hardware.html
 */
CPU::CPU(MMU* mmu) : mmu(mmu)
{
  a.set(0x01);
  f.set(0xB0);
  b.set(0x00);
  c.set(0x13);
  d.set(0x00);
  e.set(0xD8);
  h.set(0x01);
  l.set(0x4D);
  sp.set(0xFFFE);
  pc.set(0x100);

}

/**
 * tick: Fetch and execute the next opcode
 * Returns the number of cycles taken
 */
int CPU::tick()
{
  int cycles;
  handle_interrupts(); // move to some higher level tick()
  if (halted) return 1;

  word addr = pc.get();
  byte opcode = read_pc();

  if (opcode == 0xCB) {
    byte cb = read_pc();
    cycles = execute_cb(cb, addr);
  } else {
    cycles = execute(opcode, addr);
  }

  return cycles;
}

// void handle_timer(int cycles)
// {
//   div.set(div.get() + cycles);
//   clocks += cycles * 4;

//   if ((TimerControl() >> 2) & 1) {
//     unsigned int frequency;
//     switch (TimerControl() & 0x3) {
//       case 0: frequency = 4096; break;
//       case 1: frequency = 262144; break;
//       case 2: frequency = 65536; break;
//       case 3: frequency = 16384; break;
//     }

//     if (clocks >= (4194304 / frequency)) {
//     }
//   }
// }

static constexpr uint8_t interrupt_addresses[5] = { 0x40, 0x48, 0x50, 0x58, 0x60 };

void CPU::handle_interrupts()
{
  if (ime) {
    byte requests = InterruptFlag() & InterruptEnabled();

    /**
     * "The priorities follow the order of the bits in the IE and IF registers:
     * Bit 0 (VBlank) has the highest priority, and Bit 4 (Joypad) has the lowest priority."
     */

    for (int i = 0; requests; i++) {
      if (requests & 1) {
        stack_push(pc);
        pc.set(interrupt_addresses[i]);
        mmu->write(0xFF0F, InterruptEnabled() & ~(1 << i));
      }
      requests >>= 1;
    }
  }
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
  // LOG("| 0x%04X: %s (0x%x)", address, opcode_metadata[opcode].c_str(), opcode);
  // if ((address == 0xC9FF && opcode == 0x20) || (address == 0xC9FD && opcode == 0xFE)) {
  //   LOG("Flags @ 0x%04X: 0x%x, 0x%x, 0x%x, 0x%x,", address, zero_flag(), subtract_flag(), halfcarry_flag(), carry_flag() );
  // }
  // LOG("| FLAGS: 0x%x, 0x%x, 0x%x, 0x%x", f.read((uint8_t)Flag::Z_ZERO),
  //     f.read((uint8_t)Flag::N_SUBTRACT), f.read((uint8_t)Flag::H_HALFCARRY), f.read((uint8_t)Flag::C_CARRY)
  // );

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
    case 0x9E: opcode_0x9E(); break; case 0x07: opcode_0x07(); break; case 0x17: opcode_0x17(); break; case 0x0F: opcode_0x0F(); break;
    case 0x1F: opcode_0x1F(); break; case 0xC0: opcode_0xC0(); break; case 0xD0: opcode_0xD0(); break; case 0x29: opcode_0x29(); break;
    case 0xC2: opcode_0xC2(); break; case 0xD2: opcode_0xD2(); break; case 0xCA: opcode_0xCA(); break; case 0xDA: opcode_0xDA(); break;
    case 0xE9: opcode_0xE9(); break; case 0x76: opcode_0x76(); break; case 0xD9: opcode_0xD9(); break; case 0xF7: opcode_0xF7(); break;
    case 0xE7: opcode_0xE7(); break; case 0xD7: opcode_0xD7(); break; case 0xC7: opcode_0xC7(); break; case 0xFF: opcode_0xFF(); break;
    case 0xEF: opcode_0xEF(); break; case 0xDF: opcode_0xDF(); break; case 0xCF: opcode_0xCF(); break; case 0x09: opcode_0x09(); break;
    case 0x19: opcode_0x19(); break; case 0x39: opcode_0x39(); break; case 0xE8: opcode_0xE8(); break; case 0x27: opcode_0x27(); break;
    case 0x37: opcode_0x37(); break; case 0x2F: opcode_0x2F(); break; case 0x3F: opcode_0x3F(); break;

    default:
      std::cout << "Unknown opcode: 0x" << std::hex << (int)opcode << std::dec << std::endl;
      exit(1);
  }

  return cond_cycles ? TrueCycleTable[opcode] : FalseCycleTable[opcode];
}

int CPU::execute_cb(byte opcode, word address)
{
  // LOG("| 0x%04X: %s (CB 0x%x)", address, opcode_cb_metadata[opcode].c_str(), opcode);
  // LOG("| FLAGS: 0x%x, 0x%x, 0x%x, 0x%x", f.read((uint8_t)Flag::Z_ZERO),
  //     f.read((uint8_t)Flag::N_SUBTRACT), f.read((uint8_t)Flag::H_HALFCARRY), f.read((uint8_t)Flag::C_CARRY)
  // );

  switch (opcode) {
    case 0xFF: opcode_cb_0xFF(); break; case 0xFE: opcode_cb_0xFE(); break; case 0xFD: opcode_cb_0xFD(); break; case 0xFC: opcode_cb_0xFC(); break;
    case 0xFB: opcode_cb_0xFB(); break; case 0xFA: opcode_cb_0xFA(); break; case 0xF9: opcode_cb_0xF9(); break; case 0xF8: opcode_cb_0xF8(); break;
    case 0xF7: opcode_cb_0xF7(); break; case 0xF6: opcode_cb_0xF6(); break; case 0xF5: opcode_cb_0xF5(); break; case 0xF4: opcode_cb_0xF4(); break;
    case 0xF3: opcode_cb_0xF3(); break; case 0xF2: opcode_cb_0xF2(); break; case 0xF1: opcode_cb_0xF1(); break; case 0xF0: opcode_cb_0xF0(); break;
    case 0xEF: opcode_cb_0xEF(); break; case 0xEE: opcode_cb_0xEE(); break; case 0xED: opcode_cb_0xED(); break; case 0xEC: opcode_cb_0xEC(); break;
    case 0xEB: opcode_cb_0xEB(); break; case 0xEA: opcode_cb_0xEA(); break; case 0xE9: opcode_cb_0xE9(); break; case 0xE8: opcode_cb_0xE8(); break;
    case 0xE7: opcode_cb_0xE7(); break; case 0xE6: opcode_cb_0xE6(); break; case 0xE5: opcode_cb_0xE5(); break; case 0xE4: opcode_cb_0xE4(); break;
    case 0xE3: opcode_cb_0xE3(); break; case 0xE2: opcode_cb_0xE2(); break; case 0xE1: opcode_cb_0xE1(); break; case 0xE0: opcode_cb_0xE0(); break;
    case 0xDF: opcode_cb_0xDF(); break; case 0xDE: opcode_cb_0xDE(); break; case 0xDD: opcode_cb_0xDD(); break; case 0xDC: opcode_cb_0xDC(); break;
    case 0xDB: opcode_cb_0xDB(); break; case 0xDA: opcode_cb_0xDA(); break; case 0xD9: opcode_cb_0xD9(); break; case 0xD8: opcode_cb_0xD8(); break;
    case 0xD7: opcode_cb_0xD7(); break; case 0xD6: opcode_cb_0xD6(); break; case 0xD5: opcode_cb_0xD5(); break; case 0xD4: opcode_cb_0xD4(); break;
    case 0xD3: opcode_cb_0xD3(); break; case 0xD2: opcode_cb_0xD2(); break; case 0xD1: opcode_cb_0xD1(); break; case 0xD0: opcode_cb_0xD0(); break;
    case 0xCF: opcode_cb_0xCF(); break; case 0xCE: opcode_cb_0xCE(); break; case 0xCD: opcode_cb_0xCD(); break; case 0xCC: opcode_cb_0xCC(); break;
    case 0xCB: opcode_cb_0xCB(); break; case 0xCA: opcode_cb_0xCA(); break; case 0xC9: opcode_cb_0xC9(); break; case 0xC8: opcode_cb_0xC8(); break;
    case 0xC7: opcode_cb_0xC7(); break; case 0xC6: opcode_cb_0xC6(); break; case 0xC5: opcode_cb_0xC5(); break; case 0xC4: opcode_cb_0xC4(); break;
    case 0xC3: opcode_cb_0xC3(); break; case 0xC2: opcode_cb_0xC2(); break; case 0xC1: opcode_cb_0xC1(); break; case 0xC0: opcode_cb_0xC0(); break;
    case 0xBF: opcode_cb_0xBF(); break; case 0xBE: opcode_cb_0xBE(); break; case 0xBD: opcode_cb_0xBD(); break; case 0xBC: opcode_cb_0xBC(); break;
    case 0xBB: opcode_cb_0xBB(); break; case 0xBA: opcode_cb_0xBA(); break; case 0xB9: opcode_cb_0xB9(); break; case 0xB8: opcode_cb_0xB8(); break;
    case 0xB7: opcode_cb_0xB7(); break; case 0xB6: opcode_cb_0xB6(); break; case 0xB5: opcode_cb_0xB5(); break; case 0xB4: opcode_cb_0xB4(); break;
    case 0xB3: opcode_cb_0xB3(); break; case 0xB2: opcode_cb_0xB2(); break; case 0xB1: opcode_cb_0xB1(); break; case 0xB0: opcode_cb_0xB0(); break;
    case 0xAF: opcode_cb_0xAF(); break; case 0xAE: opcode_cb_0xAE(); break; case 0xAD: opcode_cb_0xAD(); break; case 0xAC: opcode_cb_0xAC(); break;
    case 0xAB: opcode_cb_0xAB(); break; case 0xAA: opcode_cb_0xAA(); break; case 0xA9: opcode_cb_0xA9(); break; case 0xA8: opcode_cb_0xA8(); break;
    case 0xA7: opcode_cb_0xA7(); break; case 0xA6: opcode_cb_0xA6(); break; case 0xA5: opcode_cb_0xA5(); break; case 0xA4: opcode_cb_0xA4(); break;
    case 0xA3: opcode_cb_0xA3(); break; case 0xA2: opcode_cb_0xA2(); break; case 0xA1: opcode_cb_0xA1(); break; case 0xA0: opcode_cb_0xA0(); break;
    case 0x9F: opcode_cb_0x9F(); break; case 0x9E: opcode_cb_0x9E(); break; case 0x9D: opcode_cb_0x9D(); break; case 0x9C: opcode_cb_0x9C(); break;
    case 0x9B: opcode_cb_0x9B(); break; case 0x9A: opcode_cb_0x9A(); break; case 0x99: opcode_cb_0x99(); break; case 0x98: opcode_cb_0x98(); break;
    case 0x97: opcode_cb_0x97(); break; case 0x96: opcode_cb_0x96(); break; case 0x95: opcode_cb_0x95(); break; case 0x94: opcode_cb_0x94(); break;
    case 0x93: opcode_cb_0x93(); break; case 0x92: opcode_cb_0x92(); break; case 0x91: opcode_cb_0x91(); break; case 0x90: opcode_cb_0x90(); break;
    case 0x8F: opcode_cb_0x8F(); break; case 0x8e: opcode_cb_0x8E(); break; case 0x8d: opcode_cb_0x8D(); break; case 0x8c: opcode_cb_0x8C(); break;
    case 0x8B: opcode_cb_0x8B(); break; case 0x8a: opcode_cb_0x8A(); break; case 0x89: opcode_cb_0x89(); break; case 0x88: opcode_cb_0x88(); break;
    case 0x87: opcode_cb_0x87(); break; case 0x86: opcode_cb_0x86(); break; case 0x85: opcode_cb_0x85(); break; case 0x84: opcode_cb_0x84(); break;
    case 0x83: opcode_cb_0x83(); break; case 0x82: opcode_cb_0x82(); break; case 0x81: opcode_cb_0x81(); break; case 0x80: opcode_cb_0x80(); break;
    case 0x7F: opcode_cb_0x7F(); break; case 0x7e: opcode_cb_0x7E(); break; case 0x7d: opcode_cb_0x7D(); break; case 0x7c: opcode_cb_0x7C(); break;
    case 0x7B: opcode_cb_0x7B(); break; case 0x7a: opcode_cb_0x7A(); break; case 0x79: opcode_cb_0x79(); break; case 0x78: opcode_cb_0x78(); break;
    case 0x77: opcode_cb_0x77(); break; case 0x76: opcode_cb_0x76(); break; case 0x75: opcode_cb_0x75(); break; case 0x74: opcode_cb_0x74(); break;
    case 0x73: opcode_cb_0x73(); break; case 0x72: opcode_cb_0x72(); break; case 0x71: opcode_cb_0x71(); break; case 0x70: opcode_cb_0x70(); break;
    case 0x6F: opcode_cb_0x6F(); break; case 0x6e: opcode_cb_0x6E(); break; case 0x6d: opcode_cb_0x6D(); break; case 0x6c: opcode_cb_0x6C(); break;
    case 0x6B: opcode_cb_0x6B(); break; case 0x6a: opcode_cb_0x6A(); break; case 0x69: opcode_cb_0x69(); break; case 0x68: opcode_cb_0x68(); break;
    case 0x67: opcode_cb_0x67(); break; case 0x66: opcode_cb_0x66(); break; case 0x65: opcode_cb_0x65(); break; case 0x64: opcode_cb_0x64(); break;
    case 0x63: opcode_cb_0x63(); break; case 0x62: opcode_cb_0x62(); break; case 0x61: opcode_cb_0x61(); break; case 0x60: opcode_cb_0x60(); break;
    case 0x5F: opcode_cb_0x5F(); break; case 0x5e: opcode_cb_0x5E(); break; case 0x5d: opcode_cb_0x5D(); break; case 0x5c: opcode_cb_0x5C(); break;
    case 0x5B: opcode_cb_0x5B(); break; case 0x5a: opcode_cb_0x5A(); break; case 0x59: opcode_cb_0x59(); break; case 0x58: opcode_cb_0x58(); break;
    case 0x57: opcode_cb_0x57(); break; case 0x56: opcode_cb_0x56(); break; case 0x55: opcode_cb_0x55(); break; case 0x54: opcode_cb_0x54(); break;
    case 0x53: opcode_cb_0x53(); break; case 0x52: opcode_cb_0x52(); break; case 0x51: opcode_cb_0x51(); break; case 0x50: opcode_cb_0x50(); break;
    case 0x4F: opcode_cb_0x4F(); break; case 0x4e: opcode_cb_0x4E(); break; case 0x4d: opcode_cb_0x4D(); break; case 0x4c: opcode_cb_0x4C(); break;
    case 0x4B: opcode_cb_0x4B(); break; case 0x4a: opcode_cb_0x4A(); break; case 0x49: opcode_cb_0x49(); break; case 0x48: opcode_cb_0x48(); break;
    case 0x47: opcode_cb_0x47(); break; case 0x46: opcode_cb_0x46(); break; case 0x45: opcode_cb_0x45(); break; case 0x44: opcode_cb_0x44(); break;
    case 0x43: opcode_cb_0x43(); break; case 0x42: opcode_cb_0x42(); break; case 0x41: opcode_cb_0x41(); break; case 0x40: opcode_cb_0x40(); break;
    case 0x3F: opcode_cb_0x3F(); break; case 0x3e: opcode_cb_0x3E(); break; case 0x3d: opcode_cb_0x3D(); break; case 0x3c: opcode_cb_0x3C(); break;
    case 0x3B: opcode_cb_0x3B(); break; case 0x3a: opcode_cb_0x3A(); break; case 0x39: opcode_cb_0x39(); break; case 0x38: opcode_cb_0x38(); break;
    case 0x37: opcode_cb_0x37(); break; case 0x36: opcode_cb_0x36(); break; case 0x35: opcode_cb_0x35(); break; case 0x34: opcode_cb_0x34(); break;
    case 0x33: opcode_cb_0x33(); break; case 0x32: opcode_cb_0x32(); break; case 0x31: opcode_cb_0x31(); break; case 0x30: opcode_cb_0x30(); break;
    case 0x2F: opcode_cb_0x2F(); break; case 0x2e: opcode_cb_0x2E(); break; case 0x2d: opcode_cb_0x2D(); break; case 0x2c: opcode_cb_0x2C(); break;
    case 0x2B: opcode_cb_0x2B(); break; case 0x2a: opcode_cb_0x2A(); break; case 0x29: opcode_cb_0x29(); break; case 0x28: opcode_cb_0x28(); break;
    case 0x27: opcode_cb_0x27(); break; case 0x26: opcode_cb_0x26(); break; case 0x25: opcode_cb_0x25(); break; case 0x24: opcode_cb_0x24(); break;
    case 0x23: opcode_cb_0x23(); break; case 0x22: opcode_cb_0x22(); break; case 0x21: opcode_cb_0x21(); break; case 0x20: opcode_cb_0x20(); break;
    case 0x1F: opcode_cb_0x1F(); break; case 0x1e: opcode_cb_0x1E(); break; case 0x1d: opcode_cb_0x1D(); break; case 0x1c: opcode_cb_0x1C(); break;
    case 0x1B: opcode_cb_0x1B(); break; case 0x1a: opcode_cb_0x1A(); break; case 0x19: opcode_cb_0x19(); break; case 0x18: opcode_cb_0x18(); break;
    case 0x17: opcode_cb_0x17(); break; case 0x16: opcode_cb_0x16(); break; case 0x15: opcode_cb_0x15(); break; case 0x14: opcode_cb_0x14(); break;
    case 0x13: opcode_cb_0x13(); break; case 0x12: opcode_cb_0x12(); break; case 0x11: opcode_cb_0x11(); break; case 0x10: opcode_cb_0x10(); break;
    case 0x0F: opcode_cb_0x0F(); break; case 0x0e: opcode_cb_0x0E(); break; case 0x0d: opcode_cb_0x0D(); break; case 0x0c: opcode_cb_0x0C(); break;
    case 0x0B: opcode_cb_0x0B(); break; case 0x0a: opcode_cb_0x0A(); break; case 0x09: opcode_cb_0x09(); break; case 0x08: opcode_cb_0x08(); break;
    case 0x07: opcode_cb_0x07(); break; case 0x06: opcode_cb_0x06(); break; case 0x05: opcode_cb_0x05(); break; case 0x04: opcode_cb_0x04(); break;
    case 0x03: opcode_cb_0x03(); break; case 0x02: opcode_cb_0x02(); break; case 0x01: opcode_cb_0x01(); break; case 0x00: opcode_cb_0x00(); break;
  }

  return CallbackCycleTable[opcode];
}
