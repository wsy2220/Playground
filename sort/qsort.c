#include "sys.h"

size_t qksort_part(int *A, size_t n)
{
	size_t i, j = 0;
	int med = A[n-1], temp;
	for(i = 0; i < n-1; i++){
		if(A[i] <= med){
			temp = A[j];
			A[j] = A[i];
			A[i] = temp;
			j++;
		}
	}
	A[n-1] = A[j];
	A[j] = med;
	return j ;
}

size_t qksort_part_r(int *A, size_t n)
{
	size_t i, j = 0;
	size_t r = rand() % (n);
	int med = A[r], temp;
	A[r] = A[n-1];
	A[n-1] = med;
	for(i = 0; i < n-1; i++){
		if(A[i] <= med){
			temp = A[j];
			A[j] = A[i];
			A[i] = temp;
			j++;
		}
	}
	A[n-1] = A[j];
	A[j] = med;
	return j;
}

void qksort(int *A, size_t n)
{
	if(n <= 1)
		return;
	size_t m;
	m = qksort_part_r(A, n);
	qksort(A, m);
	qksort(A + m + 1, n - m - 1);
}

void qksort_tail(int *A, size_t n)
{
	size_t mid;
	while(n > 1){
		mid = qksort_part(A, n);
		qksort(A, mid);
		A = A + mid + 1;
		n = n - mid - 1;
	}
}

size_t qksort_part_h(int *A, size_t n)
{
	size_t i = 0-1, j = n;
	int med = A[0], temp;
	while(i < j){
		do
			j--;
		while(A[j] > med);
		do
			i++;
		while(A[i] < med);
		temp = A[i];
		A[i] = A[j];
		A[j] = temp;
	}
	return j;
}

void qksort_h(int *A, size_t n)
{
	if(n <= 1)
		return;
	size_t m;
	m = qksort_part_h(A, n);
	qksort(A, m);
	qksort(A + m , n - m );
}

void qksort_part_eq(int *A, size_t n, size_t *eq1, size_t *eq2)
{
	size_t i, j = 0, k = 1;
	int med = A[n - 1], temp;
	for(i = 0; i < n - k; i++){
		if(A[i] < med){
			temp = A[i];
			A[i] = A[j];
			A[j] = temp;
			j++;
		}
		if(A[i] == med){
			A[i] = A[n - 1 - k];
			A[n - 1 - k] = med;
			k++;
			i--;
		}
	}
	for(i = 0; i < k; i++){
		temp = A[j + i];
		A[j + i] = A[n - 1 - i];
		A[n - 1 - i] = temp;
	}
	*eq1 = j;
	*eq2 = j + k - 1;
}

void qksort_eq(int *A, size_t n)
{
	if(n <= 1)
		return;
	size_t eq1, eq2;
	qksort_part_eq(A, n, &eq1, &eq2);
	qksort_eq(A, eq1);
	qksort_eq(A + eq2 + 1, n - eq2 - 1);
}
