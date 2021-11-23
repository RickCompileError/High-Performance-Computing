#include "Board.h"

void Board::init(){
    int i;
    for (int i=0;i<50;i++) value[i].init(), clue[i].clear();
    status = false;
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
            cout <<value[i].get(j) <<' ';
        }
        cout <<endl;
    }
}

void Board::insert_clue(int line, int num){
    clue[line].push_back(num);
}

void Board::print_one(uint64_t u){
    while (u>0){
        cout <<(u & 1);
        u >>= 1;
    }
    cout <<endl;
}

bool Board::run(){
    propogate();
    return true;
}

int Board::propogate(){
    set<int> s;
    for (int i=0;i<50;i++) s.insert(i);
    while (!s.empty()){
        int l = *s.begin();
        s.erase(s.begin());
        if (!fix(25,clue[l].size(),clue+l,value[l].get())) return 0;
        uint64_t tmp = paint(25,clue[l].size(),clue+l,value[l].get());
        value[l].set(tmp);
    }
    return 1;
}

bool Board::fix(int i, int j, vector<int> *dsp, uint64_t v){
    if (i<=0 && j==0) return true;
    if (i<=0 && j>=1) return false;
    return fix0(i,j,dsp,v) || fix1(i,j,dsp,v);
}

bool Board::fix0(int i, int j, vector<int> *dsp, uint64_t v){
    uint64_t tmp = v>>2*(25-i)<<offset;
    if (tmp==ZERO || tmp==U) return fix(i-1,j,dsp,v);
    return false;
}

bool Board::fix1(int i, int j, vector<int> *dsp, uint64_t v){
    if (j<=0 || i<dsp->at(j-1)) return false;
    int cond = dsp->at(j-1);
    uint64_t tmp = v>>2*(25-i);
    for (int i=0;i<cond;i++,tmp>>=2) if (tmp<<offset==ZERO) return false;
    if (tmp<<offset==ONE) return false;
    return fix(i-cond-1,j-1,dsp,v);
}

uint64_t Board::paint(int i, int j, vector<int> *dsp, uint64_t v){
    if (i<=0) return v;
    return ppaint(i,j,dsp,v);
}

uint64_t Board::ppaint(int i, int j, vector<int> *dsp, uint64_t v){
    bool can0 = fix0(i,j,dsp,v), can1 = fix1(i,j,dsp,v);
    // cout <<can0 <<' ' <<can1 <<endl;
    if (can0 && can1) return merge(paint0(i,j,dsp,v),paint1(i,j,dsp,v));
    if (can0) return paint0(i,j,dsp,v);
    if (can1) return paint1(i,j,dsp,v);
    // cout <<"ERROR";
    return v;
}

uint64_t Board::paint0(int i, int j, vector<int> *dsp, uint64_t v){
    return paint(i-1,j,dsp,v) & mask(i) | IZERO<<2*(25-i);
}

uint64_t Board::paint1(int i, int j, vector<int> *dsp, uint64_t v){
    int cond = dsp->at(j-1);
    uint64_t tmp = paint(i-cond-1,j-1,dsp,v) & mask((i-cond)) | IZERO<<2*(25-i-cond);
    while (cond--) tmp & mask((i-cond)) | IONE<<2*(25-i-cond);
    return tmp;
}

uint64_t Board::merge(uint64_t a, uint64_t b){
    return a | b;
}