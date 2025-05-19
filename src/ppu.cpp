#include "ppu.h"
#include "bitwise.h"

PPU::PPU(MMU* mmu) :
  mmu(mmu),
  cycles(0),
  sprite_screen(WIDTH, HEIGHT),
  background_screen(WIDTH, HEIGHT)
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
  }
};

void PPU::write_sprites()
{
  for (int sprite_num = 0; sprite_num < 40; sprite_num++)
  {
    draw_sprite(sprite_num);
  }
}
void PPU::draw_sprite(const unsigned int sprite_num)
{
  word oam_address = 0xFE00 + (sprite_num * 4);
  byte sprite_y = mmu->read(oam_address);
  byte sprite_x = mmu->read(oam_address + 1);

  if (sprite_y == 0 || sprite_y >= 160) return;
  if (sprite_x == 0 || sprite_x >= 168) return;

  unsigned int sprite_size = bitwise::test_bit(mmu->read(0xFF40), 5) ? 2 : 1;

  byte sprite_index = mmu->read(oam_address + 2);
  byte sprite_attributes = mmu->read(oam_address + 3);

  bool use_obp1 = bitwise::test_bit(sprite_attributes, 4);
  bool flip_x = bitwise::test_bit(sprite_attributes, 5);
  bool flip_y = bitwise::test_bit(sprite_attributes, 6);
  bool behind_background = bitwise::test_bit(sprite_attributes, 7);

  word sprite_tile_block = 0x8000; // block 0
  byte pixel_offset = sprite_index * 16; // 8 2-byte lines in a tile
  byte pixel_index = sprite_tile_block + pixel_offset;

  int viewport_y = sprite_y - 16;
  int viewport_x = sprite_x - 8;

  for (int y = 0; y < 8 * sprite_size; y++)
  {
    for (int x = 0; x < 8; x++)
    {
      Color tile_color = Color::White; // TODO

      int screen_y = viewport_y + y;
      int screen_x = viewport_x + x;

      Color current_color = sprite_screen.get_pixel(screen_x, screen_y);

      if (tile_color == Color::Transparent) continue;
      if (!pixel_on_screen(screen_x, screen_y)) continue;
      if (behind_background && current_color != Color::White) continue;

      Color screen_color = Color::DarkGray; // TODO
      sprite_screen.set_pixel(screen_x, screen_y, screen_color);
    }
  }
}

void PPU::update_lcd_mode(VideoMode m)
{
  mmu->PPUMode = m;
  uint8_t masked = mmu->stat.get() & 0xFC;
  mmu->write(0xFF41, masked | (uint8_t)m);
}

bool PPU::pixel_on_screen(unsigned int x, unsigned int y)
{
  return x < WIDTH && y < 144;
}
