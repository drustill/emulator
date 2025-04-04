#pragma once
#include <cstdint>

class Memory
{
  public:
    uint8_t data[0x10000]; // 64KB

    uint8_t read(uint16_t addr) ;
    void write(uint16_t addr, uint8_t value) ;
} ;
