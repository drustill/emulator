#pragma once

#include "timer.h"
#include "cpu.h"
#include "mmu.h"
#include "ppu.h"

class Emulator
{
  public:
    Emulator();

    void run();
    void tick_for(int cycles);

    void draw(void* pixels_ptr, int pitch);

    void loadROM(const std::string path)
    {
      std::memset(mmu.data, 0, sizeof(mmu.data));
      std::ifstream rom(path, std::ios::binary);
      rom.read(reinterpret_cast<char*>(mmu.data), sizeof(mmu.data));
    }

    void loadBootROM(const uint8_t* buffer)
    {
      std::copy(buffer, buffer + 256, mmu.boot);
      mmu.use_boot = true;
    }

  private:
    void tick();

    void to_argb(Color c);

    CPU cpu;
    MMU mmu;
    PPU ppu;
    Timer timer;
};
