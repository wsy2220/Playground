#include "sys.h"
#define COL  10
void print_array(int *A, size_t n)
{
	size_t i;
	printf("        ");
	for(i = 0; i < COL; i++)
		printf("%8lu",i);
	printf("\n\n");
	for(i = 0; i < n; i++){
		if(i % COL == 0){
			if(i != 0)
				printf("\n");
			printf("%8lu", i / COL);
		}
		printf("%8d", A[i]);
	}
	printf("\n");
}

/* randomly permute a given array */
void permute(int *A, size_t n)
{
	size_t i, j, k;
	int temp;
	for(i = 0; i < n; i++){
		j = rand() % n;
		k = rand() % n;
		temp = A[j];
		A[j] = A[k];
		A[k] = temp;
	}
}
	
