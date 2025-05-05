#include "mmu.h"

namespace {
  static byte serial_data = 0;
}

byte MMU::read(word addr)
{
  switch (addr) {
    case 0xFF44:
      return 0x90;
      break;

    default:
      return data[addr];
  }
}

void MMU::write(word addr, byte value)
{
  data[addr] = value;

  switch (addr) {
    case 0xFF01:
      // game just wrote a character into the serial data register
      serial_data = value;
      break;

    case 0xFF02:
      // high‐bit set = “transmit” on GameBoy hardware
      if (value & 0x80) {
        // print the last-stored byte as ASCII
        std::cout << static_cast<char>(serial_data);
        std::flush(std::cout);
      }
      break;

    default:
      // all other writes just go into data[]
      break;
  }
}
