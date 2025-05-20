#include "ppu.h"
#include "bitwise.h"

PPU::PPU(MMU* mmu) :
  mmu(mmu),
  cycles(0),
  lcd(WIDTH, HEIGHT),
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

    byte line = mmu->read(0xFF44);
    write_scanline(line);

    bool interrupt = ((mmu->stat.get() >> 3) & 1);
    if (interrupt) {
      mmu->write(0xFF0F, mmu->read(0xFF0F) | 2);
    }

    if (mmu->read(0xFF44) == 143) {
      update_lcd_mode(VideoMode::VBlank);
    } else {
      update_lcd_mode(VideoMode::OAM);
    }

    mmu->write(0xFF44, mmu->read(0xFF44) + 1);
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
      write_sprites();
      draw_lcd();
      lcd.reset();

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

void PPU::update_lcd_mode(VideoMode m)
{
  mmu->PPUMode = m;
  uint8_t masked = mmu->stat.get() & 0xFC;
  mmu->write(0xFF41, masked | (uint8_t)m);
}


void PPU::write_scanline(byte line)
{
  if (bitwise::test_bit(mmu->read(0xFF40), 0))
  {
    draw_background(line);
  }

  if (bitwise::test_bit(mmu->read(0xFF40), 5))
  {
    draw_window(line);
  }
}

void PPU::draw_background(byte line)
{
  bool use_tile_data_0 = bitwise::test_bit(mmu->read(0xFF40), 4);
  bool use_tile_map_0 = !bitwise::test_bit(mmu->read(0xFF40), 3);

  word tile_data_address = use_tile_map_0 ? 0x8000 : 0x8800;
  word tile_map_address = use_tile_map_0 ? 0x9800 : 0x9C00;

  unsigned int screen_y = line;
  for (unsigned int screen_x = 0; screen_x < WIDTH; screen_x++)
  {
    unsigned int scrolled_x = screen_x + mmu->scroll_x.get();
    unsigned int scrolled_y = screen_y + mmu->scroll_y.get();

    unsigned int bg_map_x = scrolled_x % 256;
    unsigned int bg_map_y = scrolled_y % 256;

    unsigned int tile_pixel_x = (bg_map_x / 8) % 8;
    unsigned int tile_pixel_y = (bg_map_y / 8) % 8;

    unsigned int tile_index = (tile_pixel_y * 32) + tile_pixel_x;
    word tile_id_addr = tile_map_address + tile_index;

    byte tile_id = mmu->read(tile_id_addr);

    unsigned int tile_data_mem_offset =
      use_tile_data_0 ? tile_id * 16 : (static_cast<int8_t>(tile_id) + 128) * 16;

    unsigned int tile_line_offset = tile_pixel_y * 2;

    word tile_line_data_start_address = tile_data_address + tile_data_mem_offset + tile_line_offset;

    byte pixels_low = mmu->read(tile_line_data_start_address);
    byte pixels_high = mmu->read(tile_line_data_start_address + 1);

    byte pixel_color_u8 = static_cast<uint8_t>((bitwise::test_bit(pixels_high, 7 - tile_pixel_x) << 1) | bitwise::test_bit(pixels_low, 7 - tile_pixel_x));
    Color screen_color = get_color_from_byte(pixel_color_u8);

    // background_screen.set_pixel(screen_x, screen_y, screen_color);
    lcd.set_pixel(screen_x, screen_y, screen_color);
  }
}

void PPU::draw_window(byte line)
{
  bool use_tile_data_0 = bitwise::test_bit(mmu->read(0xFF40), 4);
  bool use_tile_map_0 = !bitwise::test_bit(mmu->read(0xFF40), 3);

  word tile_data_address = use_tile_map_0 ? 0x8000 : 0x8800;
  word tile_map_address = use_tile_map_0 ? 0x9800 : 0x9C00;

  unsigned int screen_y = line;
  unsigned int scrolled_y = screen_y - mmu->window_y.get();

  if (scrolled_y > HEIGHT) return;

  for (unsigned int screen_x = 0; screen_x < WIDTH; screen_x++)
  {
    unsigned int scrolled_x = screen_x + mmu->window_x.get() - 7;

    unsigned int tile_x = scrolled_x / 8;
    unsigned int tile_y = scrolled_y / 8;

    unsigned int tile_pixel_x = scrolled_x % 8;
    unsigned int tile_pixel_y = scrolled_y % 8;

    unsigned int tile_index = (tile_y * 32) + tile_x;
    word tile_id_address = tile_map_address + tile_index;

    byte tile_id = mmu->read(tile_id_address);

    unsigned int tile_data_mem_offset =
      use_tile_data_0 ? tile_id * 16 : (static_cast<int8_t>(tile_id) + 128) * 16;

    unsigned int tile_line_offset = tile_pixel_y * 2;

    word tile_line_data_start_address = tile_data_address + tile_data_mem_offset + tile_line_offset;

    byte pixels_low = mmu->read(tile_line_data_start_address);
    byte pixels_high = mmu->read(tile_line_data_start_address + 1);

    byte pixel_color_u8 = static_cast<uint8_t>((bitwise::test_bit(pixels_high, 7 - tile_pixel_x) << 1) | bitwise::test_bit(pixels_low, 7 - tile_pixel_x));
    Color screen_color = get_color_from_byte(pixel_color_u8);

    // background_screen.set_pixel(screen_x, screen_y, screen_color);
    lcd.set_pixel(screen_x, screen_y, screen_color);
  }

}

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
      // TODO: Apply flip_y and flip_x
      Color tile_color = Color::Black; // TODO

      int screen_y = viewport_y + y;
      int screen_x = viewport_x + x;

      // Color current_color = sprite_screen.get_pixel(screen_x, screen_y);
      Color current_color = lcd.get_pixel(screen_x, screen_y);

      if (tile_color == Color::Transparent) continue;
      if (!pixel_on_screen(screen_x, screen_y)) continue;
      if (behind_background && current_color != Color::White) continue;

      // sprite_screen.set_pixel(screen_x, screen_y, tile_color);
      lcd.set_pixel(screen_x, screen_y, tile_color);
    }
  }
}

bool PPU::pixel_on_screen(unsigned int x, unsigned int y)
{
  return x < WIDTH && y < 144;
}

void PPU::register_lcd(const lcd_callback_t& _lcd_callback)
{
  lcd_callback = _lcd_callback;
}

void PPU::draw_lcd()
{
  std::cout << "DRAWING DRAWING" << std::endl;
  lcd_callback(lcd);
}

Color PPU::get_color_from_byte(byte pixel_val)
{
  switch (pixel_val) {
    case 0: return Color::White;
    case 1: return Color::LightGray;
    case 2: return Color::DarkGray;
    case 3: return Color::Black;
    default: return Color::LightGray;
  }
}
