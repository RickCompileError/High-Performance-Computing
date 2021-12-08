#include "Collector.h"

Collector::Collector(int sz){
    value = new Unit[sz];
    for (int i=0;i<sz;i++) value->init();
    this->sz = sz;
    count = 0;
}

Collector::Collector(Collector &a, Collector &b, int sz){
    value = new Unit[sz];
    for (int i=0;i<sz;i++) value->init();
    this->sz = sz;
    count = 0;
    for (int i=0;i<sz;i++)
        for (int j=1;j<=25;j++)
            if (a.get_pix(i,j)==b.get_pix(i,j) && a.get_pix(i,j)!=U)
                value[i].set(j,a.get_pix(i,j));
}

void Collector::insert(int line, int pos, uint64_t v){
    value[line].set(pos,v);
    count++;
}

Unit* Collector::get_value(int line){
    return value+line;
}

uint64_t Collector::get_pix(int line, int pix){
    return get_pixel(value[line].get(),pix);
}

void Collector::update_G(Board *board){
    for (int i=0;i<sz;i++){
        for (int j=1;j<=25;j++){
            if (get_pix(i,j)==ZERO) board->set_pix(i,j,get_pix(i,j));
            if (get_pix(i,j)==ONE) board->set_pix(i,j,get_pix(i,j));
        }
    }
}

int Collector::get_count(){
    return count;
}

void Collector::clear(){
    for (int i=0;i<sz;i++) value[i].init();
    count = 0;
}