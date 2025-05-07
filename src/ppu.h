#pragma once

#include "mmu.h"

static const int WIDTH = 160;
static const int HEIGHT = 144;

class PPU
{
  public:
    PPU(MMU* mmu);

    Color SpriteData[WIDTH][HEIGHT];
    Color BackgroundData[WIDTH][HEIGHT];

  private:
    MMU* mmu;

    Color SpriteBuffer[WIDTH][HEIGHT];
    Color BackgroundBuffer[WIDTH][HEIGHT];

};
