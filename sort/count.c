#include "sys.h"

/* assume A[] < n */
void count_sort(int *A, size_t n)
{
	int *count = malloc(sizeof(int) * n * 2);
	int *temp  = count + n;
	memset(count, 0, sizeof(int) * n);
	size_t i;
	for(i = 0; i < n; i++)
		count[A[i]] ++;
	for(i = 1; i < n; i++)
		count[i] += count[i - 1];
	for(i = n - 1; i != -1; i--){
		temp[count[A[i]] - 1] = A[i];
		count[A[i]] --;
	}
	memcpy(A, temp, sizeof(int) * n);
	free(count);
}
