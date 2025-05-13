#pragma once

#include "common.h"
#include "register.h"

#include <iostream>
#include <cstdint>

class MMU
{
  public:
    byte data[0x10000];
    byte boot[0x0100];
    byte io[0x80];

    ByteRegister lcdc;
    ByteRegister stat;

    bool use_boot = false;

    byte ie = 0;

    byte serial_data = 0;

    unsigned int divider = 0;

    byte read(word addr);
    void write(word addr, byte value);

};
