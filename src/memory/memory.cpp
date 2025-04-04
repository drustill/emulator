#include "memory.h"

void Memory::write(uint16_t addr, uint8_t value)
{
  data[addr] = value;
}

uint8_t Memory::read(uint16_t addr)
{
  return data[addr];
}
