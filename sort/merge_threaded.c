#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <pthread.h>

typedef struct {
	int *arr;
	size_t size;
} array;

void merge(int *A, size_t n1, size_t n2)
{
	int *C = malloc(sizeof(int) * (n1 + n2));
	size_t i, j, k;
	j = k = 0;
	for(i = 0; i < n1 + n2; i++){
		if(j >= n1){
			C[i] = A[k + n1];
			k++;
		}
		else if(k >= n2){
			C[i] = A[j];
			j++;
		}
		else{
			C[i] = A[j] < A[k + n1] ? A[j++] : A[n1 + (k++)];
		}
	}
	memcpy(A, C, sizeof(int) * (n1 + n2));
	free(C);
}

void *merge_sort(void *ary)
{
	array *ar = ary;
	if(ar->size <= 1)
		return NULL;
	array left = {ar->arr, ar->size / 2};
	array right = {ar->arr + left.size, ar->size - left.size};
	merge_sort(&left);
	merge_sort(&right);
	merge(ar->arr, left.size, right.size);
	return NULL;
}


#define N 0x100
int main()
{
	array ar;
	ar.arr = malloc(sizeof(int) * N);
	ar.size = N;
	size_t i;
	for(i = 0; i < N; i++){
		ar.arr[i] = rand() % N;
		printf("%d\n", ar.arr[i]);
	}
	printf("\n");
	array left = {ar.arr, ar.size / 2};
	array right = {ar.arr + left.size, ar.size - left.size};
	pthread_t tid1, tid2;
	pthread_attr_t attr;
	pthread_attr_init(&attr);
	pthread_create(&tid1, &attr, merge_sort, &left);
	pthread_create(&tid2, &attr, merge_sort, &right);
	pthread_join(tid1, NULL);
	pthread_join(tid2, NULL);
	merge(ar.arr, left.size, right.size);
	fflush(stdout);
	for(i = 0; i < N; i++)
		printf("%d\n", ar.arr[i]);
	free(ar.arr);
	return 0;
}
