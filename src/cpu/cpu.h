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

    /**
     * Opcode functions
     */
    void CPU::opcode_0x12()
    void CPU::opcode_0x22()
    void CPU::opcode_0x32()
    void CPU::opcode_0x42()

    void CPU::opcode_0x06()
    void CPU::opcode_0x16()
    void CPU::opcode_0x26()
    void CPU::opcode_0x36()

    void CPU::opcode_0x0E()
    void CPU::opcode_0x1E()
    void CPU::opcode_0x2E()
    void CPU::opcode_0x2E()

    void CPU::opcode_0x40()
    void CPU::opcode_0x41()
    void CPU::opcode_0x42()
    void CPU::opcode_0x43()
    void CPU::opcode_0x44()
    void CPU::opcode_0x45()
    void CPU::opcode_0x46()
    void CPU::opcode_0x47()

    void CPU::opcode_0x48()
    void CPU::opcode_0x49()
    void CPU::opcode_0x4A()
    void CPU::opcode_0x4B()
    void CPU::opcode_0x4C()
    void CPU::opcode_0x4D()
    void CPU::opcode_0x4E()
    void CPU::opcode_0x4F()

    void CPU::opcode_0x50()
    void CPU::opcode_0x51()
    void CPU::opcode_0x52()
    void CPU::opcode_0x53()
    void CPU::opcode_0x54()
    void CPU::opcode_0x55()
    void CPU::opcode_0x56()
    void CPU::opcode_0x57()

    void CPU::opcode_0x58()
    void CPU::opcode_0x59()
    void CPU::opcode_0x5A()
    void CPU::opcode_0x5B()
    void CPU::opcode_0x5C()
    void CPU::opcode_0x5D()
    void CPU::opcode_0x6E()
    void CPU::opcode_0x5F()

    void CPU::opcode_0x60()
    void CPU::opcode_0x61()
    void CPU::opcode_0x62()
    void CPU::opcode_0x63()
    void CPU::opcode_0x64()
    void CPU::opcode_0x65()
    void CPU::opcode_0x66()
    void CPU::opcode_0x67()

    void CPU::opcode_0x68()
    void CPU::opcode_0x69()
    void CPU::opcode_0x6A()
    void CPU::opcode_0x6B()
    void CPU::opcode_0x6C()
    void CPU::opcode_0x6D()
    void CPU::opcode_0x6E()
    void CPU::opcode_0x6F()

    void CPU::opcode_0x70()
    void CPU::opcode_0x71()
    void CPU::opcode_0x72()
    void CPU::opcode_0x73()
    void CPU::opcode_0x74()
    void CPU::opcode_0x75()
    void CPU::opcode_0x77()

    void CPU::opcode_0x78()
    void CPU::opcode_0x79()
    void CPU::opcode_0x7A()
    void CPU::opcode_0x7B()
    void CPU::opcode_0x7C()
    void CPU::opcode_0x7D()
    void CPU::opcode_0x7E()
    void CPU::opcode_0x7F()

    void CPU::opcode_0xE2()
    void CPU::opcode_0xF2()

    void CPU::opcode_0xEA()
    void CPU::opcode_0xFA()

    void CPU::opcode_0xE0()
    void CPU::opcode_0xF0()

    /**
     * Opcode implementations
     */
    void LD_r8_r8(ByteRegister& reg1, ByteRegister& reg2);
    void LD_r8_r16(ByteRegister& reg, WordRegister& reg16);
    void LD_r16_r8(WordRegister& reg16, ByteRegister& reg);

    void LD_r8_n8(ByteRegister& reg);

    void LD_addr16_n8(WordRegister& reg);

    void LD_nn16_r8(ByteRegister& reg);
    void LD_r8_nn16(ByteRegister& reg);

    void LDH_r8_n8(ByteRegister& reg);
    void LDH_n8_r8(ByteRegister& reg);
};
