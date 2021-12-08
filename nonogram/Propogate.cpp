#include "Propogate.h"
#include "Set.h"

void Propogate::procedure(Board* board, Collector &pi){
    Set* s = new Set(); //queue
    int l; //line
    vector<int>* c; //clue
    Unit* u; //unit
    uint64_t before, after;

    pi.clear();
    for (int i=0;i<50;i++) s->push(i);
    while (!s->empty()){
        l = s->pop();
        c = board->get_clue(l);
        u = board->get_value(l);
        before = u->get();
        if (!fix(25,c->size(),c,before)){
            board->status = CONFLICT;
            return;
        }
        after = paint(25,c->size(),c,before);
        if (before!=after){
            for (int i=1;i<=25;i++){
                if (get_pixel(before,i)!=get_pixel(after,i)){
                    u->set(i,get_pixel(after,i));
                    pi.insert(l,i,get_pixel(after,i));
                }
            }
            int base = l<25?25:0; //determine row or col
            int ind = l%25+1; //which index need to get
            for (int i=1;i<=25;i++){
                Unit* tmp = board->get_value(base+i-1);
                if (get_pixel(after,i)!=get_pixel(tmp->get(),ind)){
                    tmp->set(ind,get_pixel(after,i));
                    pi.insert(base+i-1,ind,get_pixel(after,i));
                    s->push(base+i-1);
                }
            }
        }
    }
    board->status = board->check()?SOLVED:INCOMPLETE;
}

bool Propogate::fix(int i, int j, vector<int> *dsp, uint64_t v){
    if (i<=0 && j==0) return true;
    if (i<=0 && j>=1) return false;
    return fix0(i,j,dsp,v) || fix1(i,j,dsp,v);
}

bool Propogate::fix0(int i, int j, vector<int> *dsp, uint64_t v){
    uint64_t tmp = get_pixel(v,i);
    if (tmp==ZERO || tmp==U) return fix(i-1,j,dsp,v);
    return false;
}

bool Propogate::fix1(int i, int j, vector<int> *dsp, uint64_t v){
    if (j<=0 || i<dsp->at(j-1)) return false;
    int cond = dsp->at(j-1);
    for (int k=0;k<cond;k++) if (get_pixel(v,(i-k))==ZERO) return false;
    if (get_pixel(v,(i-cond))==ONE) return false;
    return fix(i-cond-1,j-1,dsp,v);
}

uint64_t Propogate::paint(int i, int j, vector<int> *dsp, uint64_t v){
    if (i<=0) return v;
    return ppaint(i,j,dsp,v);
}

uint64_t Propogate::ppaint(int i, int j, vector<int> *dsp, uint64_t v){
    bool can0 = fix0(i,j,dsp,v), can1 = fix1(i,j,dsp,v);
    if (can0 && !can1) return paint0(i,j,dsp,v);
    if (!can0 && can1) return paint1(i,j,dsp,v);
    return merge(paint0(i,j,dsp,v),paint1(i,j,dsp,v));
}

uint64_t Propogate::paint0(int i, int j, vector<int> *dsp, uint64_t v){
    return set_pixel(paint(i-1,j,dsp,v),i,ZERO);
}

uint64_t Propogate::paint1(int i, int j, vector<int> *dsp, uint64_t v){
    int cond = dsp->at(j-1);
    uint64_t tmp = set_pixel(paint(i-cond-1,j-1,dsp,v),(i-cond),ZERO);
    while (cond--) tmp = set_pixel(tmp,(i-cond),ONE);
    return tmp;
}

uint64_t Propogate::merge(uint64_t a, uint64_t b){
    return a | b;
}