#include "FP1.h"
#include "Propogate.h"

void FP1::procedure(Board* board){
    Board *g0 = board->deep_copy(), *g1 = board->deep_copy();
    Collector pig(SIZE);
    Propogate propogate;
    Unit* value;
    do{
        propogate.procedure(board,pig);
        if (board->status==CONFLICT || board->status==SOLVED) return;
        // cout <<"Procedure: \n";
        // board->print_board();
        pig.update_G(g0), pig.update_G(g1);
        for (int i=0;i<SIZE && board->status!=PAINTED;i++){
            value = board->get_value(i);
            for (int j=1;j<=25 && board->status!=PAINTED;j++){
                if (get_pixel(value->get(),j)==U){
                    probe(i,j,board,g0,g1,pig);
                    if (board->status==CONFLICT || board->status==SOLVED) return ;
                }
            }
        }
    } while (pig.get_count()!=0);
}

void FP1::probe(int i, int j, Board* g, Board* g0, Board* g1, Collector &pig){
    Unit* value;
    Collector pi0(SIZE), pi1(SIZE);
    Propogate propogate;
    g0->get_value(i)->set(j,ZERO);
    g1->get_value(i)->set(j,ONE);
    propogate.procedure(g0,pi0), propogate.procedure(g1,pi1);
    // cout <<i <<' ' <<j <<' ' <<pi0.get_count() <<' ' <<pi1.get_count() <<endl;
    // cout <<g0->status <<' ' <<g1->status <<endl;
    if (g0->status==CONFLICT && g1->status==CONFLICT){
        g->status=CONFLICT;
        return;
    }
    else if (g0->status==CONFLICT) pig = pi1;
    else if (g1->status==CONFLICT) pig = pi0;
    else pig = Collector(pi0,pi1,SIZE);
    if (pig.get_count()) pig.update_G(g), g->status = PAINTED;
    else g->status = INCOMPLETE;
    // cout <<"FP1: " <<endl;
    // g->print_board();
}