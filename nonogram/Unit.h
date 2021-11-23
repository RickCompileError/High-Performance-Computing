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
#define mask(i) (uint64_t)~(U>>(offset-(25-i)*2))

class Unit{
private:
    uint64_t v;
public:
    void init();
    void set(int i, int value);
    void set(uint64_t v);
    uint64_t get();
    char get(int i);
    uint64_t compare(uint64_t v);
};

#endif