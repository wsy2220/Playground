#include "sys.h"
#include "utils.h"

size_t qksort_part_r(int *A, size_t n);

/* m <= n-1 */
int rselect(int *A, size_t n, size_t m)
{
	if(n == 1)
		return A[0];
	if(n == 0 || m >= n){
		fprintf(stderr, "invalid n or m!\n");
		exit(EXIT_FAILURE);
	}
	size_t t = qksort_part_r(A, n);
	if(t == m)
		return A[t];
	if(t > m)
		return rselect(A, t, m);
	else
		return rselect(A + t + 1, n - t - 1, m - t - 1);
}

