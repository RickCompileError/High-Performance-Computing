#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>
#include <limits.h>
#include <time.h>
#include <mpi.h>

#define BLOCK_LOW(id,p,n) ((id)*(n)/(p))
#define BLOCK_HIGH(id,p,n) (BLOCK_LOW((id)+1,p,n)-1)
#define BLOCK_SIZE(id,p,n) (BLOCK_LOW((id)+1,p,n)-BLOCK_LOW(id,p,n))
#define BLOCK_OWNER(index,p,n) (((p)*((index)+1)-1)/(n))

int i, j, k, pid, psz, err, size = 10000;
int **A, *Astorage, *b, *c, *ci;
int block_low, block_high;
int *all_block_size, *block_count;
double cost, mxcost;

void init(){
	srand(pid);
	block_low = BLOCK_LOW(pid,psz,size);
	block_high = BLOCK_HIGH(pid,psz,size);
	all_block_size = (int*)malloc(psz*sizeof(int));		
	block_count = (int*)malloc(psz*sizeof(int));
	all_block_size[0] = BLOCK_SIZE(i,psz,size);
	block_count[0] = 0;
	for (i=1;i<psz;i++){
		all_block_size[i] = BLOCK_SIZE(i,psz,size);
		block_count[i] = block_count[i-1] + all_block_size[i-1];
	}

	Astorage = (int*)malloc(all_block_size[pid]*size*sizeof(int));
	A = (int**)malloc(all_block_size[pid]*sizeof(int*));
	for (i=0;i<all_block_size[pid];i++)
		A[i] = &Astorage[i*size];
	b = (int*)malloc(size*sizeof(int));
	c = (int*)calloc(size,sizeof(int));
	ci = (int*)calloc(all_block_size[pid],sizeof(int));

	for (i=0;i<all_block_size[pid];i++){
		for (j=0;j<size;j++){
			A[i][j] = rand()%5+1;
		}
	}
	if (pid==0) for (i=0;i<size;i++) b[i] = rand()%5+1;
	MPI_Bcast(b,size,MPI_INT,0,MPI_COMM_WORLD);
}

run(){
	for (i=0;i<all_block_size[pid];i++){
		for (j=0;j<size;j++){
			ci[i] += A[i][j]*b[j];
		}
	}
	MPI_Allgatherv(ci,all_block_size[pid],MPI_INT,c,all_block_size,block_count,MPI_INT,MPI_COMM_WORLD);
}

void print(){
	printf("-------rows of %d processor's matrix A-------\n",pid);
	for (i=0;i<all_block_size[pid];i++){
		for (j=0;j<size;j++){
			printf("%d ",A[i][j]);
		}
		printf("\n");
	}
	if (pid==0){
		printf("-------vector b-------\n");
		for (i=0;i<size;i++)
			printf("%d ",b[i]);
		printf("\n");
		printf("-------answer c-------\n");
		for (i=0;i<size;i++)
			printf("%d ",c[i]);
		printf("\n");
	}
}
	
int main(int argc, char **argv){
	cost = MPI_Wtime();
	err = MPI_Init(&argc, &argv);
	err = MPI_Comm_rank(MPI_COMM_WORLD, &pid);
	err = MPI_Comm_size(MPI_COMM_WORLD, &psz);

	init();
	run();
	// print();

	cost = MPI_Wtime() - cost;
	MPI_Reduce(&cost,&mxcost,1,MPI_DOUBLE,MPI_MAX,0,MPI_COMM_WORLD);
	if (pid==0) printf("-------Cost %lf-------\n",mxcost);
	err = MPI_Finalize();
	return 0;
}	
