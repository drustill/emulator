#include "../defines.h"

class ByteRegister
{
  byte value;

  public:
    ByteRegister() : value(0) {}
    byte get() { return value; }
    void set(byte newValue) { value = newValue; }
    void increment() { value++; }
    void decrement() { value--; }
}

class WordRegister
{
  word value;

  public:
    WordRegister() : value(0) {}
    word get() { return value; }
    void set(word newValue) { value = newValue; }
    void increment() { value++; }
    void decrement() { value--; }
}

struct Flags
{
  bool zf : 1; // Zero Flag
  bool nf : 1; // Subtract Flag
  bool hf : 1; // Half Carry Flag
  bool cf : 1; // Carry Flag
};
