#include "sys.h"

typedef struct{
	int *p;
	size_t width;
	size_t height;
} young_mat;


void young_set(young_mat *mat, size_t m, size_t n, int x)
{
	*(mat->p + m * mat->width + n) = x;
}

int young_get(young_mat *mat, size_t m, size_t n)
{
	return *(mat->p + m * mat->width + n);
}

void young_print(young_mat *mat)
{
	size_t i, j;
	int x;
	for(i = 0; i < mat->height; i++){
		for(j = 0; j < mat->width; j++){
			x = young_get(mat, i, j);
			if(x == INT_MAX)
				printf("     Inf");
			else
				printf("%8d", x );
		}
		printf("\n");
	}
}

void young_minimize(young_mat *mat, size_t m, size_t n)
{
	int val_min = young_get(mat, m, n);
	if(m == mat->height -1 && n == mat->width -1)
		return;
	size_t lm = m, ln = n;
	if(m < mat->height - 1 && young_get(mat, m+1, n) < val_min){
		val_min = young_get(mat, m + 1, n);
		lm = m + 1;
	}
	if(n < mat->width - 1 && young_get(mat, m, n+1) < val_min){
		val_min = young_get(mat, m, n + 1);
		lm = m;
		ln = n + 1;
	}
	young_set(mat, lm, ln, young_get(mat, m, n));
	young_set(mat, m, n, val_min);
	if(lm != m || ln != n)
		young_minimize(mat, lm, ln);
}

int young_extract_min(young_mat *mat)
{
	if(mat->width * mat->height == 0){
		fprintf(stderr, "buffer underrun!\n");
		exit(EXIT_FAILURE);
	}
	int ret = young_get(mat, 0, 0);
	young_set(mat, 0, 0, INT_MAX);
	young_minimize(mat, 0, 0);
	return ret;
}

void young_dec(young_mat *mat, size_t m, size_t n, int x)
{
	young_set(mat, m, n, x);
	if(m == 0 && n == 0)
		return;
	size_t lm = m, ln = n;
	int val_max = young_get(mat, m, n);
	if(m > 0 && young_get(mat, m - 1, n) > val_max){
		val_max = young_get(mat, m - 1, n);
		lm = m - 1;
	}
	if(n > 0 && young_get(mat, m, n - 1) > val_max){
		val_max = young_get(mat, m, n - 1);
		lm = m;
		ln = n - 1;
	}
	young_set(mat, lm, ln, x);
	young_set(mat, m, n, val_max);
	if(lm != m || ln != n)
		young_dec(mat, lm, ln, x);
}

void young_insert(young_mat *mat, int x)
{
	young_dec(mat, mat->height-1, mat->width-1, x);
}

void young_make(young_mat *mat)
{
	size_t width = mat->width;
	size_t height = mat->height;
	young_mat temp;
	temp.p = malloc(sizeof(int) * width * height);
	temp.width = width;
	temp.height = height;
	size_t i, j;
	for(i = 0; i < height; i++)
		for(j = 0; j < width; j++)
			young_set(&temp, i, j, INT_MAX);
	for(i = 0; i < height; i++)
		for(j = 0; j < width; j++)
			young_insert(&temp, young_get(mat, i, j));
	for(i = 0; i < height; i++)
		for(j = 0; j < width; j++)
			young_set(mat, i, j, young_get(&temp, i, j));
	free(temp.p);
}
	
void young_sort(young_mat *mat)
{
	size_t width = mat->width;
	size_t height = mat->height;
	young_mat temp;
	temp.p = malloc(sizeof(int) * width * height);
	temp.width = width;
	temp.height = height;
	young_make(mat);
	size_t i, j;
	for(i = 0; i < height; i++)
		for(j = 0; j < width; j++)
			young_set(&temp, i, j, young_extract_min(mat));
	for(i = 0; i < height; i++)
		for(j = 0; j < width; j++)
			young_set(mat, i, j, young_get(&temp, i, j));
	free(temp.p);
}
	
#define W 8
#define H 9
#define N W*H
int main()
{
	int A[N];
	young_mat mat;
	mat.p = &A[0];
	mat.width = W;
	mat.height = H;
	size_t i;
	for(i = 0; i < N; i++)
		A[i] = rand() % 256;
	young_print(&mat);
	printf("\n");
	young_sort(&mat);
	young_print(&mat);
	printf("\n");
	return 0;
}

