#pragma once

#include "common.h"

#include <vector>

class ShiftRegister
{
  public:
    ShiftRegister(unsigned int width, unsigned int height);

    void set_pixel(unsigned int x, unsigned int y, Color color);
    Color get_pixel(unsigned int x, unsigned int y);

  private:
    unsigned int width;
    unsigned int height;

    unsigned int get_pixel_index(unsigned int x, unsigned int y);

    std::vector<Color> buffer;
};
