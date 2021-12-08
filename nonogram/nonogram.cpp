#include <cstdio>
#include "Board.h"
#include "Backtrack.h"

using namespace std;

void start(FILE *);

int main(){    
    FILE *myfile = fopen("in.txt","r");
    if (myfile==NULL){
        printf("Reading File Error!");
        exit(EXIT_FAILURE);
    }
    start(myfile);
    fclose(myfile);
    system("pause");
}

void start(FILE *myfile){
    int cs, num;
    char c;
    Board* board;
    while (fscanf(myfile,"$%d\n",&cs)!=EOF){
        clock_t t = clock();
        board = new Board();
        for (int i=0;i<50;i++){
            fscanf(myfile,"%d%c",&num,&c);
            while (c!='\n'){
                board->set_clue(i,num);
                fscanf(myfile,"%d%c",&num,&c);
            }
            board->set_clue(i,num);
        }
        printf("$%d\n",cs);
        board = Backtrack::procedure(board);
        printf("Cost: %.2f\n",(float)(clock()-t)/CLOCKS_PER_SEC);
        cout <<"Board Status: " <<board->status <<endl;
        board->print_board();
        cout <<endl;
    }
}