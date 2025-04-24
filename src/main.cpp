#include <fstream>
#include <iostream>
#include <cstring>
#include "cpu/cpu.h"
#include "cpu/mmu.h"

void load_rom(const std::string& path, uint8_t* buffer, size_t size)
{
  // zero out buffer
  std::memset(buffer, 0, size);

  // open file in binary
  std::ifstream file (path, std::ifstream::binary);
  if (!file.is_open()) {
    std::cout << "Bad ROM";
    return ;
  }

  // read into the buffer
  file.read(reinterpret_cast<char*>(buffer), size);

  // if (!file) {
  std::cerr << "Read " << file.gcount() << " bytes from ROM.\n";
  // }
}

int main()
{
  uint8_t Cartridge[0x200000];
  const std::string ROMPATH = "../roms/gb-test-roms/cpu_instrs/individual/06-ld r,r.gb";
  // const std::string ROMPATH = "../roms/gb-test-roms/cpu_instrs/cpu_instrs.gb";

  MMU mmu;
  load_rom(ROMPATH, Cartridge, sizeof(Cartridge));
  std::memcpy(&mmu.data[0x0000], Cartridge, 0x8000);

  CPU cpu(&mmu);

  const int MAXCYCLES = 69905;
  int cycles_this_update = 0;

  while (cycles_this_update < MAXCYCLES)
  {
    int cycles = cpu.tick();
    cycles_this_update += cycles;

    // TODO: Render
  }
}
