#include <cstring>
#include "Set.h"

Set::Set(){
    memset(exist,0,sizeof(exist));
    front = end = 0;
}

int Set::size(){
    return sz;
}

int Set::push(int i){
    if (full() || exist[i]) return -1;
    exist[i] = true;
    queue[end] = i;
    end = (end+1)%sz;
    return 1;
}

int Set::pop(){
    if (empty()) return -1;
    int val = queue[front];
    exist[val] = false;
    front = (front+1)%sz;
    return val;
}

bool Set::empty(){
    return front==end;
}

bool Set::full(){
    return front==(end+1)%sz;
}