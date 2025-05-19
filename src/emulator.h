#pragma once

#include "timer.h"
#include "cpu.h"
#include "mmu.h"
#include "ppu.h"

class Emulator
{
  public:
    Emulator();

    void run(bool& quit, const lcd_callback_t& lcd_callback);

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

    void tick();
    PPU ppu;
  private:

    CPU cpu;
    MMU mmu;
    Timer timer;
};
