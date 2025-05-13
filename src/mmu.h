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

    ByteRegister lcdc, stat;
    VideoMode PPUMode = VideoMode::HBlank;

    bool use_boot = false; // Boot ROM

    byte ie = 0; // interrupt enable

    byte serial_data = 0; // test output

    unsigned int divider = 0; // divider register

    byte read(word addr);
    void write(word addr, byte value);

};
