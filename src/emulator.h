#pragma once

#include "timer.h"
#include "cpu/cpu.h"
#include "cpu/mmu.h"

class Emulator
{
  public:
    Emulator();

    void run();
    void loadROM(const std::string path) {
      std::memset(mmu.data, 0, sizeof(mmu.data));
      std::ifstream rom(path, std::ios::binary);
      if (!rom) {
          throw std::runtime_error("Failed to open ROM file");
      }
      rom.read(reinterpret_cast<char*>(mmu.data), sizeof(mmu.data));
    }

  private:
    void tick();

    CPU cpu;
    MMU mmu;
    Timer timer;
};
