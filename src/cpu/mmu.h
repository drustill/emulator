#pragma once

#include "common.h"

#include <iostream>
#include <cstdint>

class MMU
{
  public:
    byte data[0x10000]; // 64KB
    byte io[0x80];

    byte ie = 0;

    byte serial_data = 0;

    unsigned int divider = 0;

    byte read(word addr);
    void write(word addr, byte value);

};
