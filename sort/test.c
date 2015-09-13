#include "sys.h"
#include "sort.h"

#define SIZE 0x10000000
#define SORT merge_sort
#define SEED 1


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
	int *result = malloc(sizeof(int) * SIZE);
	srand(SEED);
	for(i = 0; i < SIZE; i++){
		pool[i] = rand() % SIZE;
		result[i] = pool[i];
	}
	SORT(result, SIZE);
	if(checksort(result, SIZE, 0) == 0)
		printf("check ok!\n");
	else
		printf("check fail!\n");
	free(pool);
	free(result);
	return 0;
}


