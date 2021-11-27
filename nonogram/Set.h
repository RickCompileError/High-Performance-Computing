#ifndef SET_H
#define SET_H

#include "Board.h"

#define SET_SZ SIZE+1

class Set{
private:
    int sz = SIZE+1;
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
};

#endif