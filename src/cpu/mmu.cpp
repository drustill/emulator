#include "mmu.h"

byte MMU::read(word addr)
{
  if (addr == 0xFFFF) {
    return ie;
  } else if (addr >= 0xFF00 & addr <= 0xFF7F) {
    return io[addr - 0xFF00];
  }

  return data[addr];
}

void MMU::write(word addr, byte value)
{
  if (addr == 0xFFFF) {
    ie = value;
  } else if (addr >= 0xFF00 & addr <= 0xFF7F) {
    io[addr - 0xFF00] = value;

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
    }

  } else {
    data[addr] = value;
  }
}
