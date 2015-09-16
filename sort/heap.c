/* heap sort related operations */
#include "sys.h"

#define HEAP_PARENT(i) ((i+1)/2 - 1)
#define HEAP_LEFT(i)   ((i)*2 + 1)
#define HEAP_RIGHT(i)  ((i)*2 + 2)
#define HEAP_MAX(A)    ((A)[0])

size_t heap_level(size_t index)
{
	index++;
	size_t i, mask = ~0, flag = 1;
	for(i = 0; i < sizeof(index)*8; i++){
		if(((mask << i) & index) == (flag << i))
			break;
	}
	return i;
}



void heap_print(int *A, size_t n)
{
	size_t i, level_max, m = 0;
	level_max = heap_level(n-1);
	for(i = 0; i <= level_max; i++){
		for(; m < n && m < (1 << (i+1)) - 1; m++)
			printf("%4d", A[m]);
		printf("\n");
	}
}
	
void max_heapify(int *A, size_t n, size_t index)
{
	size_t largest = index, l, r;
	l = HEAP_LEFT(index);
	r = HEAP_RIGHT(index);
	if(l < n && A[l] > A[index])
		largest = l;
	if(r < n && A[r] > A[largest])
		largest = r;
	if(largest == index)
		return;
	int temp = A[largest];
	A[largest] = A[index];
	A[index] = temp;
	max_heapify(A, n, largest);
}

void max_heapify_loop(int *A, size_t n, size_t index)
{
	size_t largest = index, l, r;
	l = HEAP_LEFT(index);
	r = HEAP_RIGHT(index);
	if(l < n && A[l] > A[index])
		largest = l;
	if(r < n && A[r] > A[largest])
		largest = r;
	while(largest != index){
		int temp = A[largest];
		A[largest] = A[index];
		A[index] = temp;
		index = largest;
		l = HEAP_LEFT(index);
		r = HEAP_RIGHT(index);
		if(l < n && A[l] > A[index])
			largest = l;
		if(r < n && A[r] > A[largest])
			largest = r;
	}
}

void build_max_heap(int *A, size_t n)
{
	size_t i;
	for(i = n/2 - 1; i != ~0; i--)
		max_heapify(A, n, i);
}

void heap_sort(int *A, size_t n)
{
	build_max_heap(A, n);
	size_t i;
	for(i = 0; i < n - 1; i++){
		int temp = A[0];
		A[0] = A[n-1-i];
		A[n-1-i] = temp;
		max_heapify(A, n-i-1, 0);
	}
}

/* heap size decreased by 1 after this function */
int heap_extract_max(int *A, size_t n)
{
	if(n == 0){
		fprintf(stderr,"heap underflow!\n");
		exit(EXIT_FAILURE);
	}
	int ret = A[0];
	A[0] = A[n-1];
	max_heapify(A, n-1, 0);
	return ret;
}

void heap_increase_key(int *A, size_t n, size_t i, int key)
{
	int parent = HEAP_PARENT(i);
	if(parent != ~0 && A[parent] < key){
		A[i] = A[parent];
		heap_increase_key(A, n, parent, key);
	}
	else
		A[i] = key;
}

/* heap size increased by 1 after this, make sure enough memory before calling */
void heap_insert(int *A, size_t n, int key)
{
	A[n] = INT_MIN;
	heap_increase_key(A, n+1, n, key);
}

void heap_delete(int *A, size_t n, size_t i)
{
	A[i] = A[n-1];
	max_heapify(A, n-1, i);
}

