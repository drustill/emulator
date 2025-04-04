#include <fstream>
#include <iostream>
#include <cstring>
#include "cpu/cpu.h"
#include "memory/memory.h"

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

  if (!file) {
      std::cerr << "Warning: only read " << file.gcount() << " bytes from ROM.\n";
  }
}

int main()
{
  uint8_t Cartridge[0x200000];
  const std::string ROMPATH = "../roms/gb-test-roms/cpu_instrs/individual/01-special.gb";

  load_rom(ROMPATH, Cartridge, sizeof(Cartridge));

  Memory memory;
  CPU cpu(&memory);

  const int MAXCYCLES = 69905;
  int cycles_this_update = 0;

  while (cycles_this_update < MAXCYCLES)
  {
    int cycles = cpu.execute_next_opcode();
    cycles_this_update += cycles;

    // TODO: Render
  }
}
