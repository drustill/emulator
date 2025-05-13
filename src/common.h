#pragma once

#include <cstdint>

using byte = uint8_t;
using word = uint16_t;

enum class Flag
{
  Z_ZERO = 7,
  N_SUBTRACT = 6,
  H_HALFCARRY = 5,
  C_CARRY = 4,
};

enum class Color
{
  White,
  LightGray,
  DarkGray,
  Black,
  Transparent,
};

enum class VideoMode
{
  HBlank,
  VBlank,
  OAM,
  VRAM,
};
