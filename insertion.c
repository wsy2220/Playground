#include "sys.h"
void insertion(int *pool, size_t n)
{
	size_t i, j;
	int t;
	for(i = 1; i < n; i++){
		t = pool[i];
		for(j = i - 1; j >= 0; j--){
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
