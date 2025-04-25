#pragma once

#include "../definitions.h"

#include <iostream>
#include <cstdint>

class MMU
{
  public:
    byte data[0x10000]; // 64KB

    byte read(word addr);
    void write(word addr, byte value);

};
