#include "ppu.h"

PPU::PPU(MMU* mmu) :
  mmu(mmu),
  cycles(0)
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
  if (this->cycles >= 204)
  {
    this->cycles -= 204;

    // write_scanline()

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
  if (this->cycles >= 456)
  {
    if (mmu->read(0xFF44) == 144)
    {
      mmu->write(0xFF0F, mmu->read(0xFF0F) | 1);
    }


    if (mmu->read(0xFF44) == 153)
    {
      // write_sprites();
      // draw();

      mmu->write(0xFF44, 0);
      update_lcd_mode(VideoMode::OAM);
    }

    mmu->write(0xFF44, mmu->read(0xFF44) + 1);
    this->cycles -= 456;
  }
};
void PPU::oam()
{
  // Search for OBJs which overlap this line
  if (this->cycles >= 80)
  {
    this->cycles -= 80;
    bool interrupt = ((mmu->stat.get() >> 5) & 1);
    if (interrupt) {
      mmu->write(0xFF0F, mmu->read(0xFF0F) | 2);
    }

    byte lcdy = mmu->read(0xFF44);
    byte ly = mmu->read(0xFF45);
    if (lcdy == ly)
    {
      uint8_t masked = mmu->stat.get() & 0xFB;
      mmu->write(0xFF41, masked | 0x04);
      if (masked | 0x40)
      {
        mmu->write(0xFF0F, mmu->read(0xFF0F) | 2);
      }
    }
    else
    {
      uint8_t masked = mmu->stat.get() & 0xFB;
      mmu->write(0xFF41, masked);
    }

    update_lcd_mode(VideoMode::VRAM);
  }
};
void PPU::vram()
{
  if (this->cycles >= 173)
  {
    update_lcd_mode(VideoMode::HBlank);
    this->cycles -= 173;

    // TODO : ????? Where do we handle the Mode3 penalties OBJ penalty?
  }
};

void PPU::update_lcd_mode(VideoMode m)
{
  mmu->PPUMode = m;
  uint8_t masked = mmu->stat.get() & 0xFC;
  mmu->write(0xFF41, masked | (uint8_t)m);
}
