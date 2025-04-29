#include <fstream>
#include <iostream>
#include <iomanip>
#include <cstring>

#include "log.h"
#include "cpu/cpu.h"
#include "cpu/mmu.h"

int main()
{
  const std::string ROMPATH = "test/gb-test-roms/cpu_instrs/individual/06-ld r,r.gb";

  MMU mmu;
  std::memset(mmu.data, 0, sizeof(mmu.data));

  std::ifstream rom(ROMPATH, std::ios::binary);

  rom.read(reinterpret_cast<char*>(mmu.data), sizeof(mmu.data));

  CPU cpu(&mmu);

  int cycles_this_update = 0;

  while (1)
  {
    int cycles = cpu.tick();
    cycles_this_update += cycles;

    // TODO: Render
  }

  std::cout << "Cycles: " << cycles_this_update << std::endl;
  CLOSE();
}
