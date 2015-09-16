#include "sys.h"

size_t qksort_part(int *A, size_t start, size_t end)
{
	size_t i, j = start - 1;
	int med = A[end], temp;
	for(i = start; i < end; i++){
		if(A[i] <= med){
			j++;
			temp = A[j];
			A[j] = A[i];
			A[i] = temp;
		}
	}
	A[end] = A[j+1];
	A[j+1] = med;
	return j + 1;
}

void qksort(int *A, size_t n)
{
	if(n <= 1)
		return;
	size_t m;
	m = qksort_part(A, 0, n - 1);
	qksort(A, m);
	qksort(A + m + 1, n - m - 1);
}
