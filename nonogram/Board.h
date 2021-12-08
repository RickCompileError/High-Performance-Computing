#ifndef BOARD_H
#define BOARD_H

#include <iostream>
#include <vector>
#include "Unit.h"

#define SIZE 50

typedef enum {CONFLICT, INCOMPLETE, SOLVED, PAINTED} Status;

using namespace std;

class Board{
private:
    Unit* value;
    vector<int>* clue;
public:
    Board();
    Board(Unit* ,vector<int>* );
    void init();
    void set_clue(int ,int );
    vector<int>* get_clue(int );
    void set_value(int ,Unit* );
    Unit* get_value(int );
    void set_pix(int ,int ,uint64_t );
    uint64_t get_pix(int ,int );
    void print_clue();
    void print_board();
    void print_binary(uint64_t );
    void print_symbol(uint64_t );
    void update(Board* );
    bool check();
    Board* deep_copy();
    Status status;
};

#endif