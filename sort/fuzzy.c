#include "sys.h"
typedef struct{
	int lower;
	int upper;
} range;

void fuz_part(range *r, size_t n, size_t *ind1, size_t *ind2)
{
	range mid = r[n - 1], temp;
	size_t i, j = 0, k = 1;
	for(i = 0; i < n - k; i++){
		if(r[i].upper < mid.upper && r[i].lower < mid.lower){
			temp = r[i];
			r[i] = r[j];
			r[j] = temp;
			j++;
		}
		else if(r[i].lower > mid.lower && r[i].upper > mid.upper){
			continue;
		}
		else{
			if(r[i].lower > mid.lower || r[i].upper < mid.upper)
				mid = r[i];
			k++;
			temp = r[i];
			r[i] = r[n - k];
			r[n - k] = temp;
			i--;
		}
	}
	for(i = 0; i < k; i++){
		temp = r[j + i];
		r[j + i] = r[n - i - 1];	
		r[n - i - 1] = temp;
	}
	*ind1 = j;
	*ind2 = j + k - 1;
}

void fuz_sort(range *r, size_t n)
{
	if(n <= 1)
		return;
	size_t ind1, ind2;
	fuz_part(r, n, &ind1, &ind2);
	fuz_sort(r, ind1);
	fuz_sort(r + ind2 + 1, n - ind2 - 1);
}

void print_range(range *r, size_t n)
{
	size_t i;
	for(i = 0; i < n; i++)
		printf("%lu\t%-8d-->\t%-8d\n", i, r[i].lower, r[i].upper);
}

void check_fuz(range *r, size_t n)
{
	size_t i;
	range temp = r[0];
	for(i = 0; i < n; i++){
		if(r[i].upper < temp.lower){
			fprintf(stderr, "check fail: %lu\n", i);
			exit(EXIT_FAILURE);
		}
		else
			temp = r[i];
	}
	printf("Check OK!\n");
}

#define N 256
#define M 0x1000
int main()
{
	size_t i;
	range r[N];
	for(i = 0; i < N; i++){
		r[i].lower = rand() % M;
		r[i].upper = r[i].lower + rand() % 0x1000;
	}
	print_range(r, N);
	printf("\n");
	fuz_sort(r,N);
	print_range(r, N);
	printf("\n");
	check_fuz(r, N);
	return 0;
}



