#pragma once

#include "mmu.h"
#include "shiftregister.h"

const int WIDTH = 160;
const int HEIGHT = 144;

class PPU
{
  public:
    PPU(MMU* mmu);

    void tick(int cycles);

    ShiftRegister sprite_screen;
    ShiftRegister background_screen;

  private:
    MMU* mmu;
    int cycles; // AKA dots

    void hblank();
    void vblank();
    void oam();
    void vram();

    void write_sprites();
    void draw_sprite(const unsigned int sprite_index);

    void update_lcd_mode(VideoMode m);
    bool pixel_on_screen(unsigned int x, unsigned int y);
};
