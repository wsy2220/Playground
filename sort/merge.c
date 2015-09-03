#include "sys.h"
void merge(int *pool, size_t start, size_t med, size_t stop, int *buf)
{
	int *temp0 = buf ; 
	int *temp1 = buf + med - start + 2;
	size_t i, m = 0, n = 0;
	for(i = 0; i < med - start + 1; i++)
		temp0[i] = pool[start + i];
	for(i = 0; i < stop - med; i++)
		temp1[i] = pool[med + i + 1];
	temp0[med - start + 1] = INT_MAX;
	temp1[stop - med] = INT_MAX;

	for(i = 0; i < stop - start + 1; i++){
		if(temp0[m] < temp1[n])
			pool[start + i] = temp0[m++];
		else
			pool[start + i] = temp1[n++];
	}
}

void merge_sort_nobuf(int *pool, size_t start, size_t stop, int *buf)
{
	if(start < stop){
		size_t med = (start + stop) / 2;
		merge_sort_nobuf(pool, start, med, buf);
		merge_sort_nobuf(pool, med + 1, stop, buf);
		merge(pool, start, med, stop, buf);
	}
}


void merge_sort(int *pool, size_t n)
{
	int *buf = malloc((n + 2)*sizeof(int)); /* two extra positions for INT_MAX */
	if(buf == NULL){
		fprintf(stderr,"malloc failed!\n");
		exit(EXIT_FAILURE);
	}
	merge_sort_nobuf(pool, 0, n-1, buf);
	free(buf);
}
