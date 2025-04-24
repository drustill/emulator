#include <iostream>
#include "cpu.h"

/**
 * CPU constructor
 * - http://www.codeslinger.co.uk/pages/projects/gameboy/hardware.html
 */
CPU::CPU(MMU* mmu) : mmu(mmu)
{
  pc.set(0x100);
}

/**
 * tick: Fetch and execute the next opcode
 * Returns the number of cycles taken
 */
int CPU::tick()
{
  byte opcode = mmu->read(pc.get());
  pc.increment();
  return execute(opcode);
}

int CPU::execute(byte opcode)
{
  return 0;
}
