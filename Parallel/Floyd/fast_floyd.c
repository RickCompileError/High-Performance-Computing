#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>
#include <limits.h>
#include <mpi.h>

#define ll long long
#define INF 0x3f3f3f3f
#define min(x,y) ((x)<(y)?(x):(y))
#define BLOCK_LOW(id,p,n) ((id)*(n)/(p))
#define BLOCK_HIGH(id,p,n) (BLOCK_LOW((id)+1,p,n)-1)
#define BLOCK_SIZE(id,p,n) (BLOCK_LOW((id)+1,p,n)-BLOCK_LOW(id,p,n))
#define BLOCK_OWNER(index,p,n) (((p)*((index)+1)-1)/(n))

int proc_id, proc_size, ierr;
double cost, mxcost;
ll i, j, k, t, sz = 1500;
ll block_low, block_high, block_size;
ll **B, *Bstorage, *rowk;
ll **A, *Answer;
MPI_Status *status;

void print(char state[]){
	printf("---------------%s---------------\n",state);
	printf("     ");
	for (i=0;i<sz;i++) printf("%5d",i);
	printf("\n");
	for (i=0;i<sz;i++){
		printf("%5lld",i);
		for (j=0;j<sz;j++){
			if (A[i][j]==INF) printf("  INF");
			else printf("%5lld",A[i][j]);
		}
		printf("\n");
	}
}

void generate(){
	// processor allocates memory respectively
	Bstorage = (ll*)malloc(sz*block_size*sizeof(ll));
	B = (ll**)malloc(block_size*sizeof(ll*));
	for (i=0;i<block_size;i++) B[i] = &Bstorage[i*sz];
	rowk = malloc(sz*sizeof(ll));

	if (proc_id==proc_size-1){
		// allocate memory to save answer
		Answer = (ll*)malloc(sz*sz*sizeof(ll));
		A = (ll**)malloc(sz*sizeof(ll*));
		for (i=0;i<sz;i++) A[i] = &Answer[i*sz];
		// generate block data
		for (k=0;k<proc_size;k++){
			int tmp_size = BLOCK_SIZE(k,proc_size,sz);
			int tmp_low = BLOCK_LOW(k,proc_size,sz);
			for (i=0;i<tmp_size;i++){
				for (j=0;j<sz;j++){
					B[i][j] = (tmp_low+i==j?0:rand()%11+1);
					if (B[i][j]==11) B[i][j] = INF;
				}
			}
			if (k!=proc_id) MPI_Send(&B[0][0],tmp_size*sz,MPI_LONG_LONG,k,k,MPI_COMM_WORLD);
		}
	}else{
		MPI_Recv(&B[0][0],block_size*sz,MPI_LONG_LONG,proc_size-1,MPI_ANY_TAG,MPI_COMM_WORLD,status);
	}
}	

void floyd(){
	for (k=0;k<sz;k++){
		// every round, broadcast row k 
		if (BLOCK_OWNER(k,proc_size,sz)==proc_id){
			for (i=0;i<sz;i++) rowk[i] = B[k-block_low][i];
		}
		MPI_Bcast(rowk,sz,MPI_LONG_LONG,BLOCK_OWNER(k,proc_size,sz),MPI_COMM_WORLD);
		// main floyd code
		for (i=0;i<block_size;i++){
			for (j=0;j<sz;j++){
				B[i][j] = min(B[i][j],B[i][k]+rowk[j]);
			}
		}
	}
	// proc_size-1 collect all data from 0 ~ proc_size-2
	if (proc_id==proc_size-1){
		for (i=0;i<proc_size-1;i++) MPI_Recv(&A[BLOCK_LOW(i,proc_size,sz)][0],BLOCK_SIZE(i,proc_size,sz)*sz,
											MPI_LONG_LONG,i,MPI_ANY_TAG,MPI_COMM_WORLD,status);
		for (i=0;i<block_size;i++) A[block_low+i] = B[i];
	}else{
		MPI_Send(&B[0][0],block_size*sz,MPI_LONG_LONG,proc_size-1,proc_size-1,MPI_COMM_WORLD);
	}
}

int main(int argc, char **argv){
	ierr = MPI_Init(&argc, &argv);
	ierr = MPI_Comm_rank(MPI_COMM_WORLD, &proc_id);
	ierr = MPI_Comm_size(MPI_COMM_WORLD, &proc_size);
	block_low = BLOCK_LOW(proc_id,proc_size,sz);
	block_high = BLOCK_HIGH(proc_id,proc_size,sz);
	block_size = BLOCK_SIZE(proc_id,proc_size,sz);

	cost = MPI_Wtime();
	generate();
	// if (proc_id==proc_size-1) print("Before");
	floyd();
	// if (proc_id==proc_size-1) print("After");
	cost = MPI_Wtime() - cost;
	MPI_Reduce(&cost,&mxcost,1,MPI_DOUBLE,MPI_MAX,proc_size-1,MPI_COMM_WORLD);
	if (proc_id==proc_size-1) printf("------------Cost %lf------------\n",mxcost);
	
	ierr = MPI_Finalize();
	return 0;
}	
