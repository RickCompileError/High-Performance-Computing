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

int pid, psz, ierr;
double cost, mxcost;
ll i, j, k, t, sz = 1500;
ll blow, bhigh, bsize;
ll **B, *Bstorage;
MPI_Status *status;

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
	// transfer data from psz-1 to 0 ~ psz-2
	if (pid==psz-1){
		for (i=0;i<psz-1;i++) MPI_Send(Bstorage+BLOCK_LOW(i,psz,sz)*sz,BLOCK_SIZE(i,psz,sz)*sz,
										MPI_LONG_LONG,i,psz-1,MPI_COMM_WORLD);
	}else{
		MPI_Recv(Bstorage+blow*sz,bsize*sz,MPI_LONG_LONG,psz-1,MPI_ANY_TAG,MPI_COMM_WORLD,status);
	}

	for (k=0;k<sz;k++){
		// every round psz-1 broadcast B[k][0]~B[k][sz-1] and B[0][k]~B[sz-1][k]
		MPI_Bcast(Bstorage+k*sz,sz,MPI_LONG_LONG,psz-1,MPI_COMM_WORLD);
		for (i=0;i<sz;i++) MPI_Bcast(Bstorage+i*sz+k,1,MPI_LONG_LONG,psz-1,MPI_COMM_WORLD);

		// main floyd code
		for (i=blow;i<=bhigh;i++){
			for (j=0;j<sz;j++){
				B[i][j] = min(B[i][j],B[i][k]+B[k][j]);
			}
		}

		// every round, except sz-1, 0~psz-2 send next k to psz-1
		if (k+1<sz){
			if (pid==psz-1){
				j=k+1;
				if (pid!=BLOCK_OWNER(j,psz,sz))
					MPI_Recv(Bstorage+j*sz,sz,MPI_LONG_LONG,BLOCK_OWNER(j,psz,sz),MPI_ANY_TAG,MPI_COMM_WORLD,status);
				for (i=0;i<BLOCK_LOW(psz-1,psz,sz);i++,j+=sz) 
					MPI_Recv(Bstorage+j,1,MPI_LONG_LONG,BLOCK_OWNER(i,psz,sz),MPI_ANY_TAG,MPI_COMM_WORLD,status);
			}else{
				j=k+1;
				if (pid==BLOCK_OWNER(j,psz,sz))
					MPI_Send(Bstorage+j*sz,sz,MPI_LONG_LONG,psz-1,psz-1,MPI_COMM_WORLD);
				for (i=blow,j+=i*sz;i<=bhigh;i++,j+=sz)
					MPI_Send(Bstorage+j,1,MPI_LONG_LONG,psz-1,psz-1,MPI_COMM_WORLD);			}
		}
	}

	// psz-1 collect all data from 0 ~ psz-2
	if (pid==psz-1){
		for (i=0;i<psz-1;i++) MPI_Recv(Bstorage+BLOCK_LOW(i,psz,sz)*sz,BLOCK_SIZE(i,psz,sz)*sz,
										MPI_LONG_LONG,i,MPI_ANY_TAG,MPI_COMM_WORLD,status);
	}else{
		MPI_Send(Bstorage+blow*sz,bsize*sz,MPI_LONG_LONG,psz-1,psz-1,MPI_COMM_WORLD);
	}
}

void generate(){
	Bstorage = (ll*)malloc(sz*sz*sizeof(ll));
	B = (ll**)malloc(sz*sizeof(ll*));
	for (i=0;i<sz;i++) B[i] = &Bstorage[i*sz];
	if (pid==psz-1){
		for (i=0;i<sz;i++){
			for (j=0;j<sz;j++){
				Bstorage[i*sz+j] = (i==j?0:rand()%11+1);
				if (Bstorage[i*sz+j]==11) Bstorage[i*sz+j] = INF;
			}
		}
	}
}	

int main(int argc, char **argv){
	ierr = MPI_Init(&argc, &argv);
	ierr = MPI_Comm_rank(MPI_COMM_WORLD, &pid);
	ierr = MPI_Comm_size(MPI_COMM_WORLD, &psz);
	blow = BLOCK_LOW(pid,psz,sz);
	bhigh = BLOCK_HIGH(pid,psz,sz);
	bsize = BLOCK_SIZE(pid,psz,sz);

	cost = MPI_Wtime();
	generate();
	// if (pid==psz-1)	print("Before");
	floyd();
	// if (pid==psz-1) print("After");
	cost = MPI_Wtime() - cost;
	MPI_Reduce(&cost,&mxcost,1,MPI_DOUBLE,MPI_MAX,psz-1,MPI_COMM_WORLD);
	if (pid==psz-1)	printf("------------Cost %lf------------\n",mxcost);
	
	ierr = MPI_Finalize();
	return 0;
}	
