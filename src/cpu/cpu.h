#include "registers.h"
#include "../memory/memory.h" // Should change compiler flags to use "memory/memory.h"

class CPU
{
  public:
    CPU(Memory* mem);
    void execute(uint8_t opcode);

  private:
    Flags flags;
    Memory* memory;
    Registers registers;

    uint8_t& decode_reg(uint8_t code);
    void ADD(uint8_t value);
    void SUB(uint8_t value);
}
