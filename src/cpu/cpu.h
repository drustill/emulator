#include "registers.h"

class CPU
{
  public:
    CPU();
    void execute(uint8_t opcode);
  private:
    Flags flags;
    Registers registers;

    void ADD(uint8_t value);
    void LD(const uint8_t &src, uint8_t &dst);
}
