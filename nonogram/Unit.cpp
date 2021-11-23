#include "Unit.h"

void Unit::init(){
    v = 0;
    for (int i=0;i<25;i++) v = (v<<2)+IU;
}

void Unit::set(int i, int value){
    int ioffset = (25-i)*2;
    if (value==0) v = v & mask(i) | IZERO<<ioffset;
    else if (value==1) v = v & mask(i) | IONE<<ioffset;
    else v = v & mask(i) | IU<<ioffset;
}

void Unit::set(uint64_t v){
    this->v = v;
}

uint64_t Unit::get(){
    return v;
}

char Unit::get(int i){
    uint64_t val = v>>2*(25-i)<<offset;
    if (val==ZERO) return '0';
    else if (val==ONE) return '1';
    else if (val==U) return 'u';
    return 'x';
}