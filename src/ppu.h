#pragma once

#include "mmu.h"

const int WIDTH = 160;
const int HEIGHT = 144;

class PPU
{
  public:
    PPU(MMU* mmu);

    void tick(int cycles);

  private:
    MMU* mmu;
    int cycles; // AKA dots
    std::vector<Color> TileBuffer;

    void hblank();
    void vblank();
    void oam();
    void vram();
};
