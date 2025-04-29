#include "register.h"
#include "common.h"

word RegisterPair::get()
{
  word res = (hi.get() << 8) | lo.get();
  return res;
}

void RegisterPair::set(word value)
{
  lo.set(static_cast<int8_t>(value));
  hi.set(static_cast<int8_t>(value >> 8));
}

void RegisterPair::increment()
{
  set(get() + 1);
}

void RegisterPair::decrement()
{
  set(get() - 1);
}
