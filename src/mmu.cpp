#include "mmu.h"

byte MMU::read(word addr)
{
  if (use_boot && addr < 0x0100) {
    return boot[addr];
  } else if (addr == 0xFF40) {
    return lcdc.get();
  } else if (addr == 0xFF41) {
    return stat.get();
  } else if (addr == 0xFF44) {
    return scroll_y.get();
  } else if (addr == 0xFF43) {
    return scroll_x.get();
  } else if (addr == 0xFF4B) {
    return window_x.get();
  } else if (addr == 0xFF4A) {
    return window_y.get();
  } else if (addr == 0xFFFF) {
    return ie;
  } else if (addr >= 0xFF00 & addr <= 0xFF7F) {
    return io[addr - 0xFF00];
  }

  return data[addr];
}

void MMU::write(word addr, byte value)
{
  if (use_boot && addr == 0xFF50) {
    use_boot = false;
  } else if (addr == 0xFF40) {
    lcdc.set(value);
  } else if (addr == 0xFF41) {
    stat.set(value);
  } else if (addr == 0xFF42) {
    scroll_y.set(value);
  } else if (addr == 0xFF43) {
    scroll_x.set(value);
  } else if (addr == 0xFF4B) {
    window_x.set(value);
  } else if (addr == 0xFF4A) {
    window_y.set(value);
  } else if (addr == 0xFFFF) {
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

      case 0xFF04:
        divider = 0;
        io[addr - 0xFF00] = 0;
        break;
    }

  } else {
    data[addr] = value;
  }
}
