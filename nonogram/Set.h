#ifndef SET_H
#define SET_H

#include "Board.h"

#define SET_SZ SIZE+1

class Set{
private:
    int mxsz = SIZE+1;
    int sz = 0;
    bool exist[SET_SZ];
    int queue[SET_SZ];
    int front, end;
public:
    Set();
    int size();
    int push(int val);
    int pop();
    bool empty();
    bool full();
    int get_front();
    int get_end();
};

#endif