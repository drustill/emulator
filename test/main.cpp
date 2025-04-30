#include <fstream>
#include <iostream>
#include <iomanip>
#include <cstring>

#include "log.h"
#include "cpu/cpu.h"
#include "cpu/mmu.h"

int main(int argc, char* argv[])
{
  if (argc != 2) {
    std::cerr << "Usage: " << argv[0] << " <path_to_rom>" << std::endl;
    return 1;
  }

  MMU mmu;
  std::memset(mmu.data, 0, sizeof(mmu.data));

  const std::string rom_path = argv[1];
  std::ifstream rom(rom_path, std::ios::binary);

  rom.read(reinterpret_cast<char*>(mmu.data), sizeof(mmu.data));

  CPU cpu(&mmu);

  int cycles_this_update = 0;

  while (1)
  {
    int cycles = cpu.tick();
    cycles_this_update += cycles;

    // TODO: Render
  }

  CLOSE();
}
