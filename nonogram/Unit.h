#ifndef UNIT_H
#define UNIT_H

#include <cstdint>

#define ZERO (uint64_t)0x4000000000000000
#define ONE (uint64_t)0x8000000000000000
#define U (uint64_t)0xC000000000000000
#define IZERO (uint64_t)0x1
#define IONE (uint64_t)0x2
#define IU (uint64_t)0x3
#define offset (int)62
#define mask(i) (uint64_t)~(U>>(offset-2*(25-i)))
#define get_pixel(value, i) (uint64_t)value>>2*(25-i)<<offset
#define set_pixel(value, i, v) (uint64_t)value & mask(i) | v>>(offset-2*(25-i))

class Unit{
private:
    uint64_t v;
public:
    Unit();
    Unit(uint64_t );
    void init();
    void set(int ,uint64_t );
    void set(uint64_t );
    uint64_t get();
    char get_char(int );
};

#endif