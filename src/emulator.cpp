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

void Emulator::tick()
{
    int cycles = cpu.tick();
    timer.tick(cycles);
}
