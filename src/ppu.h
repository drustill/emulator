#pragma once

#include "mmu.h"

static const int WIDTH = 160;
static const int HEIGHT = 144;

typedef void (*PPUModeFunc)();

class PPU
{
  public:
    PPU(MMU* mmu);

    void tick(int cycles);

    // Color SpriteData[WIDTH][HEIGHT];
    // Color BackgroundData[WIDTH][HEIGHT];

  private:
    MMU* mmu;
    cycles = 0; // AKA dots
    std::vector<Color> TileBuffer(WIDTH * HEIGHT, Color::White);

    void Mode2OAM();
    void Mode3VRAM();
    void Mode0HBlank();
    void Mode1VBlank();

    PPUModeFunc operations[4] = {
      &PPU::Mode0HBlank,
      &PPU::Mode1VBlank
      &PPU::Mode2OAM,
      &PPU::Mode3VRAM,
    };

};
