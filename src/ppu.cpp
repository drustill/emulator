#include "ppu.h"

PPU::PPU(MMU* mmu) :
  mmu(mmu),
  cycles(0),
  TileBuffer(WIDTH * HEIGHT, Color::White)
{ }

void PPU::tick(int cycles)
{
  if (!((mmu->lcdc.get() >> 7) & 1)) { return; }
  this->cycles += cycles;

  VideoMode mode = mmu->PPUMode;

  switch (mode) {
    case VideoMode::HBlank: hblank(); break;
    case VideoMode::VBlank: vblank(); break;
    case VideoMode::OAM: oam(); break;
    case VideoMode::VRAM: vram(); break;
  }
}

void PPU::hblank() {};
void PPU::vblank() {};
void PPU::oam() {};
void PPU::vram() {};
