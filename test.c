#include <stdio.h>
#include <stdlib.h>
#include "sort.h"

#define SIZE 0x1000
#define SORT selection 
#define SEED 1

int pool[SIZE];
int result[SIZE];

/* check sorted result. direction 0 increasing, 1 decreasing
 * return 0 for success, -1 for fail */
int checksort(int *result, int n, int direction)
{
	int i;
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
	int i;
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
	return 0;
}


