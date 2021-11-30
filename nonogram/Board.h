#ifndef BOARD_H
#define BOARD_H

#include <iostream>
#include <vector>
#include "Unit.h"
#include "Propogate.h"

#define SIZE 50

typedef enum {CONFLICT, INCOMPLETE, SOLVED} Status;

using namespace std;

class Board{
private:
    Unit value[SIZE];
    vector<int> clue[SIZE];
public:
    Board();
    void init();
    void set_clue(int ,int );
    vector<int>* get_clue(int );
    Unit* get_value(int );
    void print_clue();
    void print_board();
    void print_binary(uint64_t );
    void print_symbol(uint64_t );
    void run();
    Status status;
};

#endif