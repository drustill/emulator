#include "emulator.h"

Emulator::Emulator() :
  mmu(MMU()),
  cpu(&mmu),
  ppu(&mmu),
  timer(&mmu)
{ }

void Emulator::run(bool& quit, const lcd_callback_t& lcd_callback)
{
  ppu.register_lcd(lcd_callback);

  while (!quit)
  {
    tick();
  }
}

void Emulator::tick()
{
  int cycles = cpu.tick();

  ppu.tick(cycles);
  timer.tick(cycles);
}
