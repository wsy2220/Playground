#include "sys.h"
#include "sort.h"
#include "heap.h"

#define SIZE 0x100000
#define SORT qksort_tail
#define SEED 1
#define COL  8


/* check sorted result. direction 0 increasing, 1 decreasing
 * return 0 for success, -1 for fail */
int checksort(int *result, size_t n, int direction)
{
	size_t i;
	for(i = 1; i < n; i++){
		if(result[i-1] > result[i] && direction == 0)
			return -1;
		if(result[i-1] < result[i] && direction == 1)
			return -1;
	}
	return 0;
}

void print_array(int *A, size_t n)
{
	size_t i;
	for(i = 0; i < n; i++){
		if(i % COL == 0 && i != 0)
			printf("\n");
		printf("%8d", A[i]);
	}
	printf("\n");
}

	
int main()
{
	size_t i;
	int *pool = malloc(sizeof(int) * SIZE);
	int *result = malloc(sizeof(int) * SIZE);
	srand(SEED);
	for(i = 0; i < SIZE; i++){
		pool[i] = rand() % SIZE;
		result[i] = pool[i];
	}
	//print_array(pool, SIZE);
	//printf("\n");
	clock_t start = clock();
	SORT(result, SIZE);
	printf("cpu time: %f s\n", (double)(clock()-start)/CLOCKS_PER_SEC);
	//print_array(result, SIZE);
	//printf("\n");
	if(checksort(result, SIZE, 0) == 0)
		printf("check ok!\n");
	else
		printf("check fail!\n");
	free(pool);
	free(result);
	return 0;
}

/*
#define N 31
int main()
{
	int A[N];
	size_t i;
	for(i = 0; i < N; i++)
		A[i] = N-1-i;
	heap_print(A, N);
	printf("\n");
	heap_extract_max(A, N);
	heap_print(A, N-1);
	printf("\n");
	heap_increase_key(A, N-1, 20, 40);
	heap_print(A, N-1);
	printf("\n");
	heap_insert(A, N-1, 20);
	heap_print(A, N);
	printf("\n");
	heap_delete(A, N, 4);
	heap_print(A, N-1);
	printf("\n");
	return 0;
}
*/
