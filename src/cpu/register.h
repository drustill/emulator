#include "../definitions.h"

class ByteRegister
{
  byte value;

  public:
    ByteRegister() : value(0) {}
    byte get() { return value; }
    void set(byte newValue) { value = newValue; }
    void increment() { value++; }
    void decrement() { value--; }
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

struct Flags
{
  bool zf; // Zero Flag
  bool nf; // Subtract Flag
  bool hf; // Half Carry Flag
  bool cf; // Carry Flag
};
