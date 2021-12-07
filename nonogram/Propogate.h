#ifndef PROPOGATE_H
#define PROPOGATE_H

#include <vector>
#include "Board.h"
#include "Collector.h"

using namespace std;

class Propogate{
public:
    void procedure(Board* ,Collector& );
    bool fix(int ,int ,vector<int>* ,uint64_t );
    bool fix0(int ,int ,vector<int>* ,uint64_t );
    bool fix1(int ,int ,vector<int>* ,uint64_t );
    uint64_t paint(int ,int ,vector<int>* ,uint64_t );
    uint64_t ppaint(int ,int ,vector<int>* ,uint64_t );
    uint64_t paint0(int ,int ,vector<int>* ,uint64_t );
    uint64_t paint1(int ,int ,vector<int>* ,uint64_t );
    uint64_t merge(uint64_t ,uint64_t );
};

#endif