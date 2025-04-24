#include <cstdint>
#include "register.h"
#include "mmu.h"

class CPU
{
  public:
    CPU (MMU* mmu);
    int tick();

    int execute(byte opcode);

  private:
    MMU* mmu;
    Flags flags;
    ByteRegister a, b, c, d, e, h, l;
    WordRegister af, bc, de, hl;
    WordRegister sp, pc;

} ;
