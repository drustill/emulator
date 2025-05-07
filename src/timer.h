#pragma once

#include "mmu.h"
#include "register.h"

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
