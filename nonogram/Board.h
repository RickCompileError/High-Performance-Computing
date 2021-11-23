#ifndef BOARD_H
#define BOARD_H

#include <iostream>
#include <array>
#include <vector>
#include <stack>
#include <set>
#include "Unit.h"

#define sz 25

using namespace std;

class Board{
private:
    Unit value[50];
    vector<int> clue[50];
    bool status{false};
public:
    void init();
    void insert_clue(int ,int );
    void print_clue();
    void print_board();
    void print_one(uint64_t );
    bool run();
    int propogate();
    bool fix(int ,int ,vector<int>* ,uint64_t );
    bool fix0(int ,int ,vector<int>* ,uint64_t );
    bool fix1(int ,int ,vector<int>* ,uint64_t );
    uint64_t paint(int ,int ,vector<int>* ,uint64_t);
    uint64_t ppaint(int ,int ,vector<int>* ,uint64_t );
    uint64_t paint0(int ,int ,vector<int>* ,uint64_t );
    uint64_t paint1(int ,int ,vector<int>* ,uint64_t );
    uint64_t merge(uint64_t ,uint64_t );
};

#endif