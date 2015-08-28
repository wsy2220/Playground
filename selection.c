#include "sys.h"
void selection(int *pool, size_t n)
{
	int t;
	size_t i, j, m;
	for(i = 0; i < n - 1; i++){
		t = pool[i];
		m = i;
		for(j = i + 1; j < n; j++){ /* find minimal of the left */
			if(t > pool[j]){
				t = pool[j];
				m = j;
			}
		}
		pool[m] = pool[i];
		pool[i] = t;
	}
}
