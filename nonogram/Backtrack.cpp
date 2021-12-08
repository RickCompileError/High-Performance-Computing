#include <cmath>
#include "Backtrack.h"
#include "FP1.h"

void Backtrack::choose(Board* board, int& ii, int& jj){
    int mx = 0, cal;
    for (int i=0;i<SIZE/2;i++){
        for (int j=1;j<=25;j++){
            if (board->get_pix(i,j)==U){
                int s0 = 0, s1 = 0;
                for (int k=1;k<=25;k++){
                    if (board->get_pix(25+k-1,i+1)==ZERO) s0++;
                    if (board->get_pix(25+k-1,i+1)==ONE) s1++;
                    if (board->get_pix(i,k)==ZERO) s0++;
                    if (board->get_pix(i,k)==ONE) s1++;
                }
                cal = (s0<s1?s0:s1)+abs(log(1+s0)-log(1+s1));
                if (mx<cal) mx = cal, ii = i, jj = j;
            }
        }
    }
}

Board* Backtrack::procedure(Board* g){
    FP1::procedure(g);
    if (g->status==CONFLICT) return g;
    if (g->status==SOLVED) return g;
    Board *g0 = g->deep_copy(), *g1 = g->deep_copy();
    int i, j;
    choose(g,i,j);
    g0->set_pix(i,j,ZERO), g0->set_pix(25+j-1,i+1,ZERO);
    g = g0;
    g = Backtrack::procedure(g);
    if (g->status==SOLVED) return g;
    g1->set_pix(i,j,ONE), g1->set_pix(25+j-1,i+1,ONE);
    g = g1;
    g = Backtrack::procedure(g);
    return g;
}