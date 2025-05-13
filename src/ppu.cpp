#include "ppu.h"

PPU::PPU(MMU* mmu) : mmu(mmu) { }

void PPU::tick(int cycles)
{
  // if LCD C bit 7 is 0, return
  // cycles += cycles;
  // VideoMode mode = mmu->PPUMode;
  //
  // switch (mode) {
  //   case VideoMode::OAM:
  //   case VideoMode::VRAM:
  //   case VideoMode::HBlank:
  //   case VideoMode::VBlank:
  // }
}

