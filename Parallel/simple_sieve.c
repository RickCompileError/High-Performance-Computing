#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>

#define ll long long

bool *prime;
ll i, j;

int main(int argc, char **argv){
	ll sz = atoi(argv[1])+1, count = 0;
	printf("size: %lld\n",sz-1);
	prime = (bool*)calloc(sz,sizeof(bool));
	for (i=2;i<sz;i++){
		if (!prime[i]){
			count++;
			for (j=i*i;j<sz;j+=i) prime[j] = true;
		}
	}
	printf("count: %d\n",count);
}
