struct Registers
{
  union { struct {uint8_t a, f; } uint16_t af; };
  union { struct {uint8_t b, c; } uint16_t bc; };
  union { struct {uint8_t d, e; } uint16_t de; };
  union { struct {uint8_t h, l; } uint16_t hl; };
  uint16_t sp, pc;
}

struct Flags
{
  bool z; // Zero flag
  bool n; // Subtract flag
  bool h; // Half carry flag
  bool c; // Carry flag
}
