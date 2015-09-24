#include "sys.h"
#include "sort.h"
#include "heap.h"
#include "utils.h"

#define SIZE 0x100
#define SORT qksort
#define SEED 1
#define COL  10


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

int main()
{
	size_t i;
	int *pool = malloc(sizeof(int) * SIZE);
	srand(SEED);
	for(i = 0; i < SIZE; i++){
		pool[i] = i;
	}
	permute(pool, SIZE);
	print_array(pool, SIZE);
	printf("\n");
	clock_t start = clock();
	SORT(pool, SIZE);
	printf("cpu time: %f s\n", (double)(clock()-start)/CLOCKS_PER_SEC);
	print_array(pool, SIZE);
	printf("\n");
	if(checksort(pool, SIZE, 0) == 0)
		printf("check ok!\n");
	else
		printf("check fail!\n");
	free(pool);
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
