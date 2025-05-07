#include "emulator.h"

Emulator::Emulator() :
  mmu(MMU()),
  cpu(&mmu),
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

void Emulator::tick()
{
  int cycles = cpu.tick();
  timer.tick(cycles);
}
