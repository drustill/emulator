#include "registers.h"

class CPU
{
  public:
    CPU();
    void execute(uint8_t opcode);
  private:
    Flags flags;
    Registers registers;

    uint8_t& decode_reg(uint8_t code);
    void ADD(uint8_t value);
    void SUB(uint8_t value);
}
