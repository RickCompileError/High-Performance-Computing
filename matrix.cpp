#include <bits/stdc++.h>

#include <iostream>
#include <ctime>

using namespace std;

const int sz = 5;
const int threshold = 4;
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
        double *ap, *bp, *cp;
        for (i=0;i<l;i++){
            for (j=0;j<n;j++){
                ap = &a[arow+i][acol];
                bp = &b[brow][bcol+j];
                cp = &c[crow+i][ccol+j];
                for (k=0;k<m;k++){
                    *cp += *(ap++) * *bp;
                    bp += sz;
                }
            }
        }
    }
}

void no_copy_recur_with_alg3(int arow, int acol, int brow, int bcol, int crow, int ccol, int l, int m, int n){
    int lsplit[3], msplit[3], nsplit[3];
    int i, j, k, t;
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
        double f, tmp[m];
        for (i=0;i<n;i++){
            for (t=0;t<m;t++) tmp[t] = b[brow+t][bcol+i];
            for (j=0;j<l;j++){
                f = 0;
                for (k=0;k<m;k++){
                    f += a[arow+j][acol+k]*tmp[k];
                }
                c[crow+j][ccol+i] += f;
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
    int i, j, k, t;
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
        double f, tmp[m];
        for (i=0;i<l;i++){
            for (j=0;j<m;j++){
                splita[i][j] = a[arow+i][acol+j];
            }
        }
        for (i=0;i<m;i++){
            for (j=0;j<n;j++){
                splitb[i][j] = b[brow+i][bcol+j];
            }
        }
        for (i=0;i<n;i++){
            for (t=0;t<m;t++) tmp[t] = splitb[t][i];
            for (j=0;j<l;j++){
                f = 0;
                for (k=0;k<m;k++){
                    f += splita[j][k]*tmp[k];
                }
                c[crow+j][ccol+i] += f;
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