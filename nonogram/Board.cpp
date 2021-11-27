#include "Board.h"

Board::Board(){
    int i;
    for (int i=0;i<50;i++) value[i].init(), clue[i].clear();
    status = INCOMPLETE;
}

void Board::init(){
    int i;
    for (int i=0;i<50;i++) value[i].init(), clue[i].clear();
    status = INCOMPLETE;
}

void Board::print_clue(){
    for (vector<int> i: clue){
        for (int j: i) cout <<j <<' ';
        cout <<endl;
    }
}

void Board::print_board(){
    for (int i=0;i<25;i++){
        for (int j=1;j<=25;j++){
            cout <<value[i].get_char(j) <<' ';
        }
        cout <<endl;
    }
}

void Board::set_clue(int line, int num){
    clue[line].push_back(num);
}

vector<int>* Board::get_clue(int line){
    return clue+line;
}

Unit* Board::get_value(int line){
    return value+line;
}

void Board::print_one(uint64_t u){
    while (u>0){
        cout <<(u & 1);
        u >>= 1;
    }
    cout <<endl;
}

void Board::run(){
    Propogate* pro = new Propogate();
    pro->procedure(this);
}