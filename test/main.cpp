#include <fstream>
#include <iostream>
#include <iomanip>
#include <cstring>

#include "log.h"
#include "emulator.h"

static void draw(const ShiftRegister& buffer)
{}

int main(int argc, char* argv[])
{
  if (argc != 2) {
    std::cerr << "Usage: " << argv[0] << " <path_to_rom>" << std::endl;
    return 1;
  }

  Emulator emulator;

  const std::string rom_path = argv[1];
  emulator.loadROM(rom_path);

  bool quit = false;

  emulator.run(quit, draw);

  CLOSE();
}
