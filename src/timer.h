#pragma once

#include "cpu/mmu.h"
#include "cpu/register.h"

static constexpr int CLOCK_HZ = 4194304;

class Timer
{
  public:
    Timer(MMU* mmu);
    void tick(int cycles);
  private:
    MMU* mmu;

    int clocks = 0;
};
