#include "sys.h"

#define N 0x100
#define M 5

typedef int obj[M];

void sort_stable(obj **p, size_t m, size_t n)
{
	size_t i, j;
	obj *temp;
	for(i = 1; i < n; i++){
		j = i;
		while(j > 0 && (*p[j])[m] < (*p[j-1])[m]){
			temp = p[j];
			p[j] = p[j-1];
			p[j-1] = temp;
			j--;
		}
	}
}

void radix_sort(obj **p, size_t m, size_t n)
{
	size_t i;
	for(i = m - 1; i != -1; i--)
		sort_stable(p, i, n);
}

void print_obj(obj **p, size_t n)
{
	size_t i, j;
	for(i = 0; i < n; i++){
		for(j = 0; j < M; j++)
			printf("%d\t", (*p[i])[j]);
		printf("\n");
	}
}

int main()
{
	obj pt[N];
	size_t i, j;
	for(i = 0; i < N; i++)
		for(j = 0; j < M; j++)
			pt[i][j] = rand() % 5;
	obj *p[N];
	for(i = 0; i < N; i++)
		p[i] = &pt[i];
	print_obj(p, N);
	printf("\n");
	radix_sort(p, M, N);
	print_obj(p, N);
	printf("\n");
	return 0;
}
