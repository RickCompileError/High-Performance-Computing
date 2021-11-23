#include <cstdio>
#include "Board.h"

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
    Board board;
    while (fscanf(myfile,"$%d\n",&cs)!=EOF){
        board.init();
        clock_t t = clock();
        for (int i=0;i<50;i++){
            fscanf(myfile,"%d%c",&num,&c);
            while (c!='\n'){
                board.insert_clue(i,num);
                fscanf(myfile,"%d%c",&num,&c);
            }
            board.insert_clue(i,num);
        }
        board.run();
        board.print_board();
        printf("Case %d cost: %.2f\n",cs,(float)(clock()-t)/CLOCKS_PER_SEC);
    }
}