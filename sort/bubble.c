#include "sys.h"

void bubble_sort(int *pool, size_t n)
{
	size_t i, j;
	int t;
	for(i = 0; i < n - 1; i++)
		for(j = n - 1; j > i; j--)
			if(pool[i] > pool[j]){
				t = pool[i];
				pool[i] = pool[j];
				pool[j] = t;
			}
}
