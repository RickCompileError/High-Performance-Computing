#include "Board.h"

Board::Board(){
    for (int i=0;i<50;i++) value[i].init(), clue[i].clear();
    status = INCOMPLETE;
}

void Board::init(){
    for (int i=0;i<50;i++) value[i].init(), clue[i].clear();
    status = INCOMPLETE;
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

void Board::print_binary(uint64_t u){
    vector<int> v;
    for (int i=0;i<64;i++){
        v.push_back(u&1);
        u >>= 1;
    }
    for (vector<int>::reverse_iterator it = v.rbegin();it!=v.rend();it++) cout <<(*it);
    cout <<endl;
}

void Board::print_symbol(uint64_t u){
    Unit unit(u);
    for (int i=1;i<=25;i++) cout <<unit.get_char(i) <<' ';
    cout <<endl;
}

void Board::run(){
    Propogate* pro = new Propogate();
    pro->procedure(this);
}