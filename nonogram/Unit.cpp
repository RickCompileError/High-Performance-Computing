#include "Unit.h"

Unit::Unit(){
    v = 0;
    for (int i=0;i<25;i++) v = (v<<2)+IU;
}

void Unit::init(){
    v = 0;
    for (int i=0;i<25;i++) v = (v<<2)+IU;
}

void Unit::set(int pos, uint64_t v){
    this->v = set_pixel(this->v,pos,v);
}

void Unit::set(uint64_t v){
    this->v = v;
}

uint64_t Unit::get(){
    return v;
}

char Unit::get_char(int i){
    uint64_t val = get_pixel(v,i);
    if (val==ZERO) return '0';
    else if (val==ONE) return '1';
    else if (val==U) return 'u';
    return 'x';
}