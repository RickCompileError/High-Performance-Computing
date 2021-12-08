#ifndef BACKTRACK_H
#define BACKTRACK_H

#include "Board.h"

class Backtrack{
public:
    static void choose(Board* ,int& ,int& );
    static Board* procedure(Board* );
};

#endif