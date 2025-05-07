#include "timer.h"

Timer::Timer(MMU* mmu) : mmu(mmu)
{ }

void Timer::tick(int cycles)
{
  mmu->divider += cycles;
  if (mmu->divider >= 256) {
    mmu->divider %= 256;
    mmu->write(0xFF04, mmu->divider);
  }
  clocks += cycles * 4;

  if (mmu->read(0xFF07) & 0x04) {
    unsigned int freq;
    switch (mmu->read(0xFF07) & 0x03) {
      case 0:
        freq = 4096;
        break;
      case 1:
        freq = 262144;
        break;
      case 2:
        freq = 65536;
        break;
      case 3:
        freq = 16384;
        break;
    }

    if (clocks >= CLOCK_HZ / freq) {
      clocks %= CLOCK_HZ / freq;

      if (mmu->read(0xFF05) == 0xFF) {
        mmu->write(0xFF0F, (mmu->read(0xFF0F) & ~(1 << 2)));
        mmu->write(0xFF05, mmu->read(0xFF06));
      } else {
        mmu->write(0xFF05, mmu->read(0xFF05) + 1);
      }
    }
  }
}
