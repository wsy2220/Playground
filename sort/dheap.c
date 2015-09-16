/* d-ary tree, starts from 0 */
#include "sys.h"

#define D 4

#define PARENT(i) (((i)-1)/D)
#define CHILD(i,j)  ((i)*D + (j) + 1)

typedef struct {
	int *p;
	size_t n;
} dheap;

void max_dheapify(dheap *dheap_p, size_t i)
{
	size_t j, child, ind_max = i, n = dheap_p -> n;
	int stor, *A = dheap_p -> p;
	for(j = 0; j < D && CHILD(i, j) < n; j++){
		child = CHILD(i,j);
		if(A[child] > A[ind_max])
			ind_max = child;
	}
	if(ind_max != i){
		stor = A[ind_max];
		A[ind_max] = A[i];
		A[i] = stor;
		max_dheapify(dheap_p, ind_max);
	}
}

int dheap_extract(dheap *dheap_p)
{
	if(dheap_p->n == 0){
		fprintf(stderr, "heap underrun\n");
		exit(EXIT_FAILURE);
	}
	int ret = *(dheap_p->p);
	(dheap_p -> n)--;
	if(dheap_p->n > 0){
		*(dheap_p->p) = *(dheap_p->p + dheap_p->n);
		max_dheapify(dheap_p, 0);
	}
	return ret;
}

void dheap_increase(dheap *dheap_p, size_t i, int x)
{
	int *A = dheap_p->p;
	if(x < A[i]){
		fprintf(stderr, "wrong x!\n");
		exit(EXIT_FAILURE);
	}
	A[i] = x;
	if(i == 0)
		return;
	size_t parent = PARENT(i);
	if(A[parent] < x){
		A[i] = A[parent];
		dheap_increase(dheap_p, parent, x);
	}
}

void dheap_insert(dheap *dheap_p, int x)
{
	(dheap_p->n)++;
	size_t n = dheap_p -> n;
	*(dheap_p->p + n - 1) = INT_MIN;
	dheap_increase(dheap_p, n - 1, x);
}

void dheap_print(dheap *dheap_p)
{
	size_t i, j = 0, l = 1;
	for(i = 0; i < dheap_p->n; i++){
		printf("%-4d", *(dheap_p->p + i));
		j++;
		if(j >= l){
			printf("\n");
			j = 0;
			l *= D;
		}
	}
	printf("\n");
}

#define N 40
int main()
{
	dheap heap;
	int A[N];
	size_t i;
	for(i = 0; i < N; i++)
		A[i] = N-i-1;
	heap.p = &A[0];
	heap.n = N;
	dheap_print(&heap);
	printf("\n");
	dheap_extract(&heap);
	dheap_print(&heap);
	printf("\n");
	dheap_insert(&heap, 50);
	dheap_print(&heap);
	printf("\n");
	for(i = 0; i < N; i++)
		printf("%4d", dheap_extract(&heap));
	printf("\n");
	return 0;
}
