#include "sys.h"

/* binary search for t in pool[n], assuming pool
 * is sorted in increasing order */
size_t bin_search(int *pool, size_t n, int t, int *status)
{
	size_t result = n / 2, upper = n - 1, lower = 0;
	if(n == 1){
		*status = 1;
		return 0;
	}
	if(n == 0){
		fprintf(stderr,"wrong argument for bin_search.\n");
		exit(1);
	}
	while(pool[result] != t && result > lower && result < upper){
		printf("%lu\n", result);
		if(pool[result] > t){
			upper = result;
			result = lower + (upper - lower) / 2;
		}
		else{
			lower = result;
			result = lower + (upper + 1 - result) / 2;
		}
	}
	if(pool[result] == t)
		*status = 1;
	else
		*status = 0;
	return result;
}

void insertion(int *pool, size_t n)
{
	size_t i, j;
	int t;
	for(i = 1; i < n; i++){
		t = pool[i];
		for(j = i - 1; j != ~0; j--){
			if(t < pool[j]){
				pool[j+1] = pool[j];
				pool[j] = t;
			}
			else
				break;
		}
	}
}

/* recurrsive version */
void insert_rec(int *pool, size_t n)
{
	if(n > 1){
		insert_rec(pool, n-1);
		size_t i;
		int t = pool[n-1];
		/* Caution! no sign for n */
		for(i = n - 2; i > 0; i--){ 
			if(pool[i] > t){
				pool[i+1] = pool[i];
				pool[i] = t;
			}
		}
		if(i == 0 && pool[0] > t){
			pool[1] = pool[0];
			pool[0] = t;
		}

	}
}
