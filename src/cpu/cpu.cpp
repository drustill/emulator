#include <iostream>
#include "cpu.h"

/**
 * CPU constructor
 * - http://www.codeslinger.co.uk/pages/projects/gameboy/hardware.html
 */
CPU::CPU(Memory* mem) : memory(mem)
{
  registers.pc = 0x100;
}

/**
 * tick: Fetch and execute the next opcode
 * Returns the number of cycles taken
 */
int CPU::tick()
{
  byte opcode = mmu->read(pc++);
  return execute(opcode);
}

int CPU::execute(byte opcode)
{
  // Big switch statement to functions
}
