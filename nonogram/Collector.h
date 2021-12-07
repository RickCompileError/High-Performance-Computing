#ifndef COLLECTOR_H
#define COLLECTOR_H

#include "Board.h"
#include "Unit.h"

class Collector{
private:
    Unit* value;
    int sz;
    int count;
public:
    Collector(int );
    Collector(Collector& ,Collector& ,int );
    void insert(int ,int ,uint64_t );
    Unit* get_value(int );
    void update_G(Board* );
    int get_count();
    void clear();
};

#endif