#include "common.h"

class ByteRegister
{
  byte value;

  public:
    ByteRegister() : value(0) {}
    byte get() { return value; }
    void set(byte newValue) { value = newValue; }
    void increment() { value++; }
    void decrement() { value--; }

    /* Only for register f - should be changed*/
    bool read(const byte offset) { return (value >> offset) & 0x1; }
    void write(const byte offset, const bool cond) { cond ? value |= (0x01 << offset) : value &= ~(0x01 << offset); }
};

class WordRegister
{
  word value;

  public:
    WordRegister() : value(0) {}
    word get() { return value; }
    void set(word newValue) { value = newValue; }
    void increment() { value++; }
    void decrement() { value--; }
};


class RegisterPair
{
  ByteRegister& hi;
  ByteRegister& lo;

  public:
    RegisterPair(ByteRegister& hi, ByteRegister& lo) : hi(hi), lo(lo) {}

    byte high() { return hi.get(); }
    byte low() { return lo.get(); }

    word get();
    void set(word value);

    void increment();
    void decrement();

};

enum class Flag
{
  Z_ZERO = 7,
  N_SUBTRACT = 6,
  H_HALFCARRY = 5,
  C_CARRY = 4,
};
