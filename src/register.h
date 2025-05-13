#pragma once

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

    /*
     * Only for register f - should be changed
     * Update: LCD Control may also use
     */
    bool read(const byte offset) { return (value >> offset) & 0x1; }
    void write(const byte offset, const bool cond) { cond ? value |= (0x01 << offset) : value &= ~(0x01 << offset); }
};

class WordRegister
{
  word value;

  public:
    WordRegister() : value(0) {}

    byte high() { return (value >> 8) & 0xFF; }
    byte low() { return value & 0xFF; }

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
