#include "mmu.h"

byte MMU::read(word addr)
{
  switch (addr) {
    default:
      return data[addr];
  }
}

void MMU::write(word addr, byte value)
{
  data[addr] = value;

  switch (addr) {
    case 0xFF01:
      serial_data = value;
      break;

    case 0xFF02:
      if (value & 0x80) {
        std::cout << static_cast<char>(serial_data);
        std::flush(std::cout);
      }
      break;

    default:
      break;
  }
}
