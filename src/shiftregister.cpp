#include "shiftregister.h"

ShiftRegister::ShiftRegister(unsigned int width, unsigned int height) :
  width(width),
  height(height),
  buffer(width*height, Color::White)
{ }

void ShiftRegister::set_pixel(unsigned int x, unsigned int y, Color color)
{
  buffer[get_pixel_index(x, y)] = color;
}

Color ShiftRegister::get_pixel(unsigned int x, unsigned int y) const
{
  return buffer.at(get_pixel_index(x, y));
}

unsigned int ShiftRegister::get_pixel_index(unsigned int x, unsigned int y) const
{
  return (y * width) + x;
}
