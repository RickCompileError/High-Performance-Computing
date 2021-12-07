#include "Board.h"

Board::Board(){
    value = new Unit[SIZE];
    clue = new vector<int>[SIZE];
    for (int i=0;i<50;i++) value[i].init(), clue[i].clear();
    status = INCOMPLETE;
}

Board::Board(Unit *u, vector<int> *v){
    this->value = u;
    this->clue = v;
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

void Board::set_value(int line, Unit* num){
    value[line].set(num->get());
}

Unit* Board::get_value(int line){
    return value+line;
}

void Board::print_clue(){
    for (int i=0;i<SIZE;i++){
        for (int j: clue[i]) cout <<j <<' ';
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

void Board::update(Board *board){
    for (int i=0;i<SIZE;i++) this->set_value(i,board->get_value(i));
}

bool Board::check(){
    for (int i=0;i<SIZE;i++)
        for (int j=1;j<=25;j++)
            if (get_pixel(value[i].get(),j)==U) return false;
    return true;
}

Board* Board::deep_copy(){
    Unit *u = new Unit[SIZE];
    for (int i=0;i<SIZE;i++) u[i] = Unit(value[i].get());
    vector<int> *v = clue;
    return new Board(u,v);
}