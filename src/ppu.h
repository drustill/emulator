#pragma once

#include "mmu.h"

const int WIDTH = 160;
const int HEIGHT = 144;

class PPU
{
  public:
    PPU(MMU* mmu);

    void tick(int cycles);

    std::vector<Color> sprite_data;
    std::vector<Color> background_data;

  private:
    MMU* mmu;
    int cycles; // AKA dots

    std::vector<Color> sprite_buffer;
    std::vector<Color> background_buffer;

    void hblank();
    void vblank();
    void oam();
    void vram();

    void update_lcd_mode(VideoMode m);
};
