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

struct Flags
{
  bool zf; // Zero Flag
  bool nf; // Subtract Flag
  bool hf; // Half Carry Flag
  bool cf; // Carry Flag
};
