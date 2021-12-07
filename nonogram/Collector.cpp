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
    Unit *u1, *u2;
    for (int i=0;i<sz;i++){
        u1 = a.get_value(i);
        u2 = b.get_value(i);
        for (int j=0;j<=25;j++){
            if (get_pixel(u1->get(),j)==get_pixel(u2->get(),j) && get_pixel(u1->get(),j)!=U){
                value[i].set(j,get_pixel(u1->get(),j));
                count++;
            }
        }
    }
}

void Collector::insert(int line, int pos, uint64_t v){
    value[line].set(pos,v);
    count++;
}

Unit* Collector::get_value(int line){
    return value+line;
}

void Collector::update_G(Board *board){
    Unit *updater, *updated;
    for (int i=0;i<sz;i++){
        updater = get_value(i);
        updated = board->get_value(i);
        for (int j=0;j<=25;j++){
            if (get_pixel(updater->get(),j)!=get_pixel(updated->get(),j) && 
                get_pixel(updater->get(),j)!=U) updated->set(j,get_pixel(updater->get(),j));
        }
    }
    // cout <<"Collector: " <<endl;
    // board->print_board();
}

int Collector::get_count(){
    return count;
}

void Collector::clear(){
    for (int i=0;i<sz;i++) value[i].init();
    count = 0;
}