#include "emulator.h"

Emulator::Emulator() :
  mmu(MMU()),
  cpu(&mmu),
  ppu(&mmu),
  timer(&mmu)
{ }

void Emulator::run()
{
  while (1)
  {
    tick();
  }
}

void Emulator::tick_for(int max_cycles)
{
  int done = 0;
  while (done < max_cycles) {
    int c = cpu.tick();
    timer.tick(c);
    done += c;
  }
}

uint32_t to_argb(Color c) {
    switch(c) {
      case Color::White:     return 0xFFFFFFFF;
      case Color::LightGray: return 0xFFAAAAAA;
      case Color::DarkGray:  return 0xFF555555;
      case Color::Black:     return 0xFF000000;
      default:               return 0xFFFF00FF;
    }
}

void Emulator::draw(void* pixels_ptr, int pitch)
{
  const int WIDTH = 160;
  const int HEIGHT = 144;
  uint32_t* dst = (uint32_t*)pixels_ptr;
  for (int y = 0; y < HEIGHT; ++y) {
    for (int x = 0; x < WIDTH; ++x) {
      // dst[y*(pitch/4) + x] = to_argb(ppu.buffer.at((y * WIDTH) + x));
    }
  }
}

void Emulator::tick()
{
  int cycles = cpu.tick();
  timer.tick(cycles);
}
