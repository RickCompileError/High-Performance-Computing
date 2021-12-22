#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <limits.h>
#include <mpi.h>

#define ll long long
#define BLOCK_LOW(id,p,n) ((id)*(n)/(p))
#define BLOCK_HIGH(id,p,n) (BLOCK_LOW((id)+1,p,n)-1)
#define BLOCK_SIZE(id,p,n) (BLOCK_LOW((id)+1,p,n)-BLOCK_LOW(id,p,n))
#define BLOCK_OWNER(index,p,n) (((p)*((index)+1)-1)/(n))

bool *arr;
int ierr, id, psz;
ll sz, count;
ll bsz, blow, bhigh, bcount;
ll i, j;
double cost;

int main(int argc, char **argv){
    ierr = MPI_Init(&argc, &argv);
    ierr = MPI_Comm_rank(MPI_COMM_WORLD, &id);
    ierr = MPI_Comm_size(MPI_COMM_WORLD, &psz);
    // sz = (ll)atof(argv[1])+1 // for manual input
    sz = 500000001;
    arr = calloc(sz,sizeof(bool));
    bsz = BLOCK_SIZE(id,psz,sz);
    blow = BLOCK_LOW(id,psz,sz);
    bhigh = BLOCK_HIGH(id,psz,sz);
    
    cost = MPI_Wtime();
    if (id==0) arr[0] = arr[1] = true;
    i = 2, count = 0, bcount = 0;
    while (i*i<=sz){
        j = (i*i>=blow?i*i:(blow+(i-blow%i)%i));
        for (;j<=bhigh;j+=i) arr[j] = true;
        j = (i>=blow?i+1:blow);
        for (;j<=bhigh && arr[j];j++);
        if (j>bhigh) j = sz;
        MPI_Reduce(&j,&i,1,MPI_LONG_LONG,MPI_MIN,0,MPI_COMM_WORLD);
        MPI_Bcast(&i,1,MPI_LONG_LONG,0,MPI_COMM_WORLD);
    }
    for (j=blow;j<=bhigh;j++) if (!arr[j]) bcount++;
    
    printf("[%d] from %lld ~ %lld, size %lld, found %lld primes.\n",id,blow,bhigh,bsz,bcount);
    MPI_Reduce(&bcount,&count,1,MPI_LONG_LONG,MPI_SUM,0,MPI_COMM_WORLD);
    if (id==0){
        printf("-------------------------Result-------------------------\n");
        printf("Processor size = %d\n",psz);
        printf("Search range from 0 ~ %d\n",sz-1);
        printf("Total prime = %d\n",count);
        printf("Total cost = %lf\n",MPI_Wtime()-cost);
        //printf("-------------------------Result-------------------------\n");
    }
    MPI_Finalize();
    return 0;
}
