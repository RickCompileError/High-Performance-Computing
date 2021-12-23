#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>
#include <limits.h>
#include <time.h>

#define ll long long
#define INF 0x3f3f3f3f
#define min(x,y) ((x)<(y)?(x):(y))

ll i, j, k, sz = 10;
ll **B, *Bstorage;

void print(char state[]){
	printf("---------------%s---------------\n",state);
	printf("     ");
	for (i=0;i<sz;i++) printf("%5d",i);
	printf("\n");
	for (i=0;i<sz;i++){
		printf("%5lld",i);
		for (j=0;j<sz;j++){
			if (B[i][j]==INF) printf("  INF");
			else printf("%5lld",B[i][j]);
		}
		printf("\n");
	}
}

void floyd(){
	for (k=0;k<sz;k++)
		for (i=0;i<sz;i++)
			for (j=0;j<sz;j++)
				B[i][j] = min(B[i][j],B[i][k]+B[k][j]);
}

void generate(){
	Bstorage = (ll*)malloc(sz*sz*sizeof(ll));
	for (i=0;i<sz;i++){
		for (j=0;j<sz;j++){
			Bstorage[i*sz+j] = (i==j?0:rand()%11+1);
			if (Bstorage[i*sz+j]==11) Bstorage[i*sz+j] = INF;
		}
	}
	B = (ll**)malloc(sz*sizeof(ll*));
	for (i=0;i<sz;i++) B[i] = &Bstorage[i*sz];
}	

int main(int argc, char **argv){	
	clock_t t = clock();
	generate();
	print("Before");
	floyd();
	print("After");
	printf("------------Cost %f------------\n",(float)(clock()-t)/CLOCKS_PER_SEC);
	return 0;
}	
