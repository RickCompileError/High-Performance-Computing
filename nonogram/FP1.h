#ifndef FP1_H
#define FP1_H

#include "Board.h"
#include "Collector.h"

class FP1{
public:
    static void procedure(Board* );
    static void probe(int ,int ,Board* ,Board* ,Board* ,Collector& );
};

#endif