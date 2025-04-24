#pragma once

#include "../defines.h"

#include <cstdint>

class MMU
{
  public:
    byte data[0x10000]; // 64KB

    byte read(word addr) { return data[addr]; }
    void write(word addr, byte value) { data[addr] = value; }
} ;
