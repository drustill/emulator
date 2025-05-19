#pragma once

#include "common.h"

namespace bitwise
{
  inline byte set_bit(byte value, int bit)
  {
    return value | (1 << bit);
  }

  inline byte clear_bit(byte value, int bit)
  {
    return value & ~(1 << bit);
  }

  inline bool test_bit(byte value, int bit)
  {
    return (value >> bit) & 1;
  }
}
