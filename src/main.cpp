#include <fstream>
#include <iostream>
#include <iomanip>
#include <cstring>
#include "cpu/cpu.h"
#include "cpu/mmu.h"
#include "logger.h"

const int MAXCYCLES = 69905;

int main()
{
  const std::string ROMPATH = "../roms/gb-test-roms/cpu_instrs/individual/06-ld r,r.gb";

  MMU mmu;
  std::memset(mmu.data, 0, sizeof(mmu.data));

  std::ifstream rom(ROMPATH, std::ios::binary);

  rom.read(reinterpret_cast<char*>(mmu.data), sizeof(mmu.data));

  CPU cpu(&mmu);

  int cycles_this_update = 0;

  while (cycles_this_update < MAXCYCLES)
  {
    int cycles = cpu.tick();
    cycles_this_update += cycles;

    // TODO: Render
  }

  CLOSE();
}
