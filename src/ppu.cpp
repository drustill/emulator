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

void PPU::hblank()
{
  // Wait until the end of scanline
  if (this->cycles >= 456)
  {
    this->cycles -= 456;
    bool interrupt = ((mmu->stat.get() >> 3) & 1);

    if (interrupt) {
      mmu->write(0xFF0F, mmu->read(0xFF0F) | 2);
    }

    if (mmu->read(0xFF44) == 143) {
      update_lcd_mode(VideoMode::VBlank);
      mmu->write(0xFF40, 0); // LY
    } else {
      update_lcd_mode(VideoMode::OAM);
    }
  }
};
void PPU::vblank()
{
  // Wait until next frame
};
void PPU::oam()
{
  // Search for OBJs which overlap this line
};
void PPU::vram()
{
  // Sending pixels to the LCD
};

void update_lcd_mode(VideoMode m)
{
  mmu->PPUMode = m;
  uint8_t masked = mmu->stat.get() & 0xFC;
  mmu-write(0xFF41, masked | (uint8_t)m);
}
