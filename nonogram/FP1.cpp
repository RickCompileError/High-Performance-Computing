#include "FP1.h"
#include "Propogate.h"

void FP1::procedure(Board* board){
    Collector pig(SIZE);
    Propogate propogate;
    do{
        propogate.procedure(board,pig);
        if (board->status==CONFLICT || board->status==SOLVED) return;
        for (int i=0;i<SIZE && board->status!=PAINTED;i++){
            for (int j=1;j<=25 && board->status!=PAINTED;j++){
                if (board->get_pix(i,j)==U){
                    probe(i,j,board,pig);
                    if (board->status==CONFLICT || board->status==SOLVED) return ;
                }
            }
        }
    } while (pig.get_count()!=0);
}

void FP1::probe(int i, int j, Board* g, Collector &pig){
    Board *g0 = g->deep_copy(), *g1 = g->deep_copy();
    Unit* value;
    Collector pi0(SIZE), pi1(SIZE);
    Propogate propogate;
    g0->set_pix(i,j,ZERO), g0->set_pix(25+j-1,i+1,ZERO);
    g1->set_pix(i,j,ONE), g1->set_pix(25+j-1,i+1,ONE);
    propogate.procedure(g0,pi0), propogate.procedure(g1,pi1);
    pi0.insert(i,j,ZERO), pi0.insert(25+j-1,i+1,ZERO);
    pi1.insert(i,j,ONE), pi1.insert(25+j-1,i+1,ONE);
    if (g0->status==CONFLICT && g1->status==CONFLICT){
        g->status=CONFLICT;
        return;
    }
    else if (g0->status==CONFLICT) pig = pi1;
    else if (g1->status==CONFLICT) pig = pi0;
    else pig = Collector(pi0,pi1,SIZE);
    if (pig.get_count()) pig.update_G(g), g->status = PAINTED;
    else g->status = INCOMPLETE;
}