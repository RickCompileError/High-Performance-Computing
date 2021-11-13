#include <bits/stdc++.h>

#include <iostream>
#include <ctime>

using namespace std;

const int sz = 1500;
const int threshold = 5000;
double a[sz][sz], b[sz][sz], c[sz][sz];

void printmatrix(){
    for (int i=0;i<sz;i++){
        for (int j=0;j<sz;j++) cout <<setw(2) <<a[i][j] <<' ';
        if (i!=sz/2) cout <<"   ";
        else cout <<" x ";
        for (int j=0;j<sz;j++) cout <<setw(2) <<b[i][j] <<' ';
        cout <<endl;
    }
}

void print(){
    for (int i=0;i<sz;i++){
        for (int j=0;j<sz;j++){
            cout <<c[i][j] <<' ';
        }
        cout <<endl;
    }
}

void clear(){
    for (int i=0;i<sz;i++) for (int j=0;j<sz;j++) c[i][j] = 0;
}

void rand_init(){
    for (int i=0;i<sz;i++){
        for (int j=0;j<sz;j++){
            a[i][j] = rand()%10+1;
            b[i][j] = rand()%10+1;
        }
    }
    clear();
}

void init(){
    for (int i=0;i<sz;i++){
        for (int j=0;j<sz;j++){
            a[i][j] = 1.1;
            b[i][j] = 1.1;
        }
    }
    clear();
}

void alg1(){
    clock_t t = clock();
    register int i, j, k;
    register double f;
    for (i=0;i<sz;i++){
        for (j=0;j<sz;j++){
            f = 0;
            for (k=0;k<sz;k++){
                f += a[i][k]*b[k][j];
            }
            c[i][j] = f;
        }
    }
    cout <<"Algo1 cost time: " <<(float)(clock()-t)/CLOCKS_PER_SEC <<endl;
}

void alg2(){
    clock_t t = clock();
    register int i, j, k;
    register double f;
    for (i=0;i<sz;i++){
        for (j=0;j<sz;j++){
            f = a[i][j];
            for (k=0;k<sz;k++) c[i][k] += f*b[j][k];
        }
    }
    cout <<"Algo2 cost time: " <<(float)(clock()-t)/CLOCKS_PER_SEC <<endl;
}

void alg3(){
    clock_t t = clock();
    register int i, j, k, l;
    register double f, tmp[sz];
    for (i=0;i<sz;i++){
        for (l=0;l<sz;l++) tmp[l] = b[l][i];
        for (j=0;j<sz;j++){
            f = 0;
            for (k=0;k<sz;k++){
                f += a[j][k]*tmp[k];
            }
            c[j][i] = f;
        }
    }
    cout <<"Algo3 cost time: " <<(float)(clock()-t)/CLOCKS_PER_SEC <<endl;
}

void no_copy_recur_with_alg2(int arow, int acol, int brow, int bcol, int crow, int ccol, int l, int m, int n){
    int lsplit[3], msplit[3], nsplit[3];
    int i, j, k;
    if (m*n>threshold){
        lsplit[0] = 0, lsplit[1] = l/2, lsplit[2] = l - l/2;
        msplit[0] = 0, msplit[1] = m/2, msplit[2] = m - m/2;
        nsplit[0] = 0, nsplit[1] = n/2, nsplit[2] = n - n/2;
        for (i=0;i<2;i++)
            for (j=0;j<2;j++)
                for (k=0;k<2;k++)
                    no_copy_recur_with_alg2(arow+lsplit[i], acol+msplit[k],
                                brow+msplit[k], bcol+nsplit[j],
                                crow+lsplit[i], ccol+nsplit[j],
                                lsplit[i+1], msplit[k+1], nsplit[j+1]);
    }else{
        register double *ap, *bp, *cp;
        register int ii, jj, kk;
        for (ii=0;ii<l;ii++){
            for (jj=0;jj<n;jj++){
                ap = &a[arow+ii][acol];
                bp = &b[brow][bcol+jj];
                cp = &c[crow+ii][ccol+jj];
                for (kk=0;k<m;kk++){
                    *cp += *(ap++) * *bp;
                    bp += sz;
                }
            }
        }
    }
}

void no_copy_recur_with_alg3(int arow, int acol, int brow, int bcol, int crow, int ccol, int l, int m, int n){
    int lsplit[3], msplit[3], nsplit[3];
    int i, j, k;
    if (m*n>threshold){
        lsplit[0] = 0, lsplit[1] = l/2, lsplit[2] = l - l/2;
        msplit[0] = 0, msplit[1] = m/2, msplit[2] = m - m/2;
        nsplit[0] = 0, nsplit[1] = n/2, nsplit[2] = n - n/2;
        for (i=0;i<2;i++)
            for (j=0;j<2;j++)
                for (k=0;k<2;k++)
                    no_copy_recur_with_alg3(arow+lsplit[i], acol+msplit[k],
                                brow+msplit[k], bcol+nsplit[j],
                                crow+lsplit[i], ccol+nsplit[j],
                                lsplit[i+1], msplit[k+1], nsplit[j+1]);
    }else{
        register int ii, jj, kk, tt;
        register double f, tmp[m];
        for (ii=0;ii<n;ii++){
            for (tt=0;tt<m;tt++) tmp[tt] = b[brow+tt][bcol+ii];
            for (jj=0;jj<l;jj++){
                f = 0;
                for (kk=0;kk<m;kk++){
                    f += a[arow+jj][acol+kk]*tmp[kk];
                }
                c[crow+jj][ccol+ii] += f;
            }
        }
    }
}

void alg4(){
    clock_t t = clock();
    no_copy_recur_with_alg3(0, 0, 0, 0, 0, 0, sz, sz, sz);
    cout <<"Algo4 cost time: " <<(float)(clock()-t)/CLOCKS_PER_SEC <<endl;
}

void copy_matrix_recur_with_alg3(int arow, int acol, int brow, int bcol, int crow, int ccol, int l, int m, int n){
    int lsplit[3], msplit[3], nsplit[3];
    int i, j, k;
    if (m*n>threshold){
        lsplit[0] = 0, lsplit[1] = l/2, lsplit[2] = l - l/2;
        msplit[0] = 0, msplit[1] = m/2, msplit[2] = m - m/2;
        nsplit[0] = 0, nsplit[1] = n/2, nsplit[2] = n - n/2;
        for (i=0;i<2;i++)
            for (j=0;j<2;j++)
                for (k=0;k<2;k++)
                    copy_matrix_recur_with_alg3(arow+lsplit[i], acol+msplit[k],
                                brow+msplit[k], bcol+nsplit[j],
                                crow+lsplit[i], ccol+nsplit[j],
                                lsplit[i+1], msplit[k+1], nsplit[j+1]);
    }else{
        int splita[l][m], splitb[m][n];
        register int ii, jj, kk, tt;
        register double f, tmp[m];
        for (ii=0;ii<l;ii++){
            for (jj=0;jj<m;jj++){
                splita[ii][jj] = a[arow+ii][acol+jj];
            }
        }
        for (ii=0;ii<m;ii++){
            for (jj=0;jj<n;jj++){
                splitb[ii][jj] = b[brow+ii][bcol+jj];
            }
        }
        for (ii=0;ii<n;ii++){
            for (tt=0;tt<m;tt++) tmp[tt] = splitb[tt][ii];
            for (jj=0;jj<l;jj++){
                f = 0;
                for (kk=0;kk<m;kk++){
                    f += splita[jj][kk]*tmp[kk];
                }
                c[crow+jj][ccol+ii] += f;
            }
        }
    }
}

void alg5(){
    clock_t t = clock();
    copy_matrix_recur_with_alg3(0, 0, 0, 0, 0, 0, sz, sz, sz);
    cout <<"Algo5 cost time: " <<(float)(clock()-t)/CLOCKS_PER_SEC <<endl;
}

int main(){
    rand_init();
    // printmatrix();

    alg1();
    // print();
    clear();

    alg2();
    // print();
    clear();
    
    alg3();
    // print();
    clear();
    
    alg4();
    // print();
    clear();

    alg5();
    // print();
    clear();

}

/* 
size = 1500, threshold = 4
Algo1 cost time: 18.484
Algo2 cost time: 9.733
Algo3 cost time: 9.623
Algo4 cost time: 31.855
Algo5 cost time: 37.113

size = 1500, threshold = 500
Algo1 cost time: 18.091
Algo2 cost time: 9.535
Algo3 cost time: 9.358
Algo4 cost time: 10.588
Algo5 cost time: 10.146

size = 1500, threshold = 1000
Algo1 cost time: 18.258
Algo2 cost time: 9.588
Algo3 cost time: 9.389
Algo4 cost time: 9.523
Algo5 cost time: 9.59

size = 1500, threshold = 2500
Algo1 cost time: 18.361
Algo2 cost time: 9.728
Algo3 cost time: 9.526
Algo4 cost time: 9.698
Algo5 cost time: 9.86

size = 1500, threshold = 5000
Algo1 cost time: 18.401
Algo2 cost time: 9.72
Algo3 cost time: 9.436
Algo4 cost time: 9.429
Algo5 cost time: 9.555

size = 1500, threshold = 10000
Algo1 cost time: 18.217
Algo2 cost time: 9.582
Algo3 cost time: 9.409
Algo4 cost time: 9.882
Algo5 cost time: 10.171

*/