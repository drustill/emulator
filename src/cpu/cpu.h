#include "registers.h"
#include "../memory/memory.h" // Should change compiler flags to use "memory/memory.h"

class CPU
{
  public:
    CPU(Memory* mem);
    int execute_next_opcode();

  private:
    Flags flags;
    Memory* memory;
    Registers registers;

    int execute(uint8_t opcode);
    uint8_t& decode_reg(uint8_t code);
    uint8_t fetch_byte();
    void ADD(uint8_t value);
    void SUB(uint8_t value);
}
