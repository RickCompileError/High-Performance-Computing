#include <stdio.h>
#include <limits.h>
#include <mpi.h>
#include <stdbool.h>

#define usi unsigned short int
#define min(a,b) ((a)<(b)?(a):(b))

int i, sz, id, splsz, count, sum;
int start, end;
double cost, mxcost;
bool v[16];

void print(int num){
        printf("%d) ",id);
        for (i=0;i<16;i++) printf("%d",v[i]);
        printf(" = %d\n",num);
}

bool circuit(){
        return (((((v[0] || v[1]) && (!v[1] || !v[3])) && ((v[2] || v[3]) && (!v[3] || !v[4]))) &&
                        (((v[4] || !v[5]) && (v[5] || v[6])) && ((v[5] || !v[6]) && (v[7] || !v[8])))) &&
                        ((((v[8] || v[9]) && (v[8] || !v[9])) && ((!v[9] || !v[10]) && (v[10] || v[11])))) &&
                        (((v[11] || v[9]) && (v[12] || v[13])) && ((!v[7] || !v[13]) && ((v[13] || !v[14]) &&
                        ((v[14] || v[15]) && (!v[15] || v[6]))))));
}

void run(int id){
        start = splsz*id, end = min(splsz*(id+1),2<<16), count = 0;
        for (start;start<end;start++){
                int tmp = start;
                for (i=15;i>=0;i--) v[i]=tmp&1, tmp>>=1;
                if (circuit()) print(start), count++;
        }
}

int main(int argc, char **argv){
        cost = MPI_Wtime();
        int ierr;
        ierr = MPI_Init(&argc, &argv);
        ierr = MPI_Comm_rank(MPI_COMM_WORLD, &id);
        ierr = MPI_Comm_size(MPI_COMM_WORLD, &sz);
        splsz = (USHRT_MAX+1)/sz+((USHRT_MAX+1)%sz!=0);
        run(id);
        cost = MPI_Wtime() - cost;
        MPI_Reduce(&count,&sum,1,MPI_INT,MPI_SUM,0,MPI_COMM_WORLD);
        MPI_Reduce(&cost,&mxcost,1,MPI_DOUBLE,MPI_MAX,0,MPI_COMM_WORLD);
        printf("Process %d is done\n", id);
        if (id==0) printf("Size = %d, Total = %d, Cost = %lf\n",sz,sum,mxcost);
        ierr = MPI_Finalize();
        return 0;
}
