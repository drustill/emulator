#pragma once

#include "mmu.h"
#include "shiftregister.h"

const int WIDTH = 160;
const int HEIGHT = 144;

using lcd_callback_t = std::function<void(const ShiftRegister&)>;

class PPU
{
  public:
    PPU(MMU* mmu);

    void tick(int cycles);

    void register_lcd(const lcd_callback_t& _lcd_callback);

    ShiftRegister sprite_screen;
    ShiftRegister background_screen;
    ShiftRegister lcd;

  private:
    MMU* mmu;

    int cycles;
    lcd_callback_t lcd_callback;

    void hblank();
    void vblank();
    void oam();
    void vram();

    void update_lcd_mode(VideoMode m);

    void write_scanline(byte line);
    void draw_background(byte line);
    void draw_window(byte line);

    void write_sprites();
    void draw_sprite(const unsigned int sprite_index);

    void draw_lcd();

    bool pixel_on_screen(unsigned int x, unsigned int y);

    Color get_color_from_byte(byte pixel_val);
};
