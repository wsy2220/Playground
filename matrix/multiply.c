#include <stdio.h>
#include <stdlib.h>

void print_array(ssize_t row, ssize_t col,int A[row][col])
{
	ssize_t i, j;
	for(i = 0; i < row; i++){
		for(j = 0; j < col; j++)
			printf("%-8d", A[i][j]);
		printf("\n");
	}
}

void mul_std(ssize_t n, int A[n][n], int B[n][n], int C[n][n]) 
{
	ssize_t i, j, k;
	int temp;
	for(i = 0; i < n; i++)
		for(j = 0; j < n; j++)
			C[i][j] = 0;
	for(i = 0; i < n; i++){
		for(k = 0; k < n; k++){
			temp = A[i][k];
			for(j = 0; j < n; j++){
				C[i][j] += temp * B[k][j];
			}
		}
	}
}

void add_mat(ssize_t n, int *A, int *B, int *C)
{
	ssize_t i, j;
	for(i = 0; i < n; i++)
		for(j = 0; j < n; j++)
			C[i*n + j] = A[i*n + j] + B[i*n + j];
}

void sub_mat(ssize_t n, int *A, int *B, int *C)
{
	ssize_t i, j;
	for(i = 0; i < n; i++)
		for(j = 0; j < n; j++)
			C[i*n + j] = A[i*n + j] - B[i*n + j];
}

void mul_stras(ssize_t n, int *A, int *B, int *C)
{
	if(n == 1){
		C[0] = A[0] * B[0];
		return;
	}
	int *A00, *A01, *A10, *A11;
	int *B00, *B01, *B10, *B11;
	int *C0, *C1;
	A00 = malloc(sizeof(int) * (n*n*2 + n*n/2));
	A01 = A00 + n*n/4;
	A10 = A01 + n*n/4;
	A11 = A10 + n*n/4;
	B00 = A11 + n*n/4;
	B01 = B00 + n*n/4;
	B10 = B01 + n*n/4;
	B11 = B10 + n*n/4;
	C0  = B11 + n*n/4;
	C1  = C0  + n*n/4;
	ssize_t i, j;
	for(i = 0; i < n/2; i++){
		for(j = 0; j < n/2; j++){
			A00[j + i*n/2] = A[i*n + j];
			B00[j + i*n/2] = B[i*n + j];
			A01[j + i*n/2] = A[i*n + j + n/2];
			B01[j + i*n/2] = B[i*n + j + n/2];
			A10[j + i*n/2] = A[(i + n/2)*n + j];
			B10[j + i*n/2] = B[(i + n/2)*n + j];
			A11[j + i*n/2] = A[(i + n/2)*n + j + n/2];
			B11[j + i*n/2] = B[(i + n/2)*n + j + n/2];
		}
	}

	mul_stras(n/2, A00, B00, C0);
	mul_stras(n/2, A01, B10, C1);
	for(i = 0; i < n/2; i++)
		for(j = 0; j < n/2; j++)
			C[i*n + j] = C0[j + i*n/2] + C1[j + i*n/2];

	mul_stras(n/2, A00, B01, C0);
	mul_stras(n/2, A01, B11, C1);
	for(i = 0; i < n/2; i++)
		for(j = 0; j < n/2; j++)
			C[i*n + j + n/2] = C0[j + i*n/2] + C1[j + i*n/2];

	mul_stras(n/2, A10, B00, C0);
	mul_stras(n/2, A11, B10, C1);
	for(i = 0; i < n/2; i++)
		for(j = 0; j < n/2; j++)
			C[(i + n/2)*n + j] = C0[j + i*n/2] + C1[j + i*n/2];

	mul_stras(n/2, A10, B01, C0);
	mul_stras(n/2, A11, B11, C1);
	for(i = 0; i < n/2; i++)
		for(j = 0; j < n/2; j++)
			C[(i + n/2)*n + j + n/2] = C0[j + i*n/2] + C1[j + i*n/2];

	free(A00);
}

void mul_stras_b(ssize_t n, int *A, int *B, int *C)
{
	if(n == 1){
		C[0] = A[0] * B[0];
		return;
	}
	int *A00, *A01, *A10, *A11;
	int *B00, *B01, *B10, *B11;
	int *S[10], *P[7];
	ssize_t i, j;
	A00 = malloc(sizeof(int) * n*n/4 * 25);
	A01 = A00 + n*n/4;
	A10 = A01 + n*n/4;
	A11 = A10 + n*n/4;
	B00 = A11 + n*n/4;
	B01 = B00 + n*n/4;
	B10 = B01 + n*n/4;
	B11 = B10 + n*n/4;
	for(i = 0; i < 10; i++)
		S[i] = B11 + (i+1)*n*n/4;
	for(i = 0; i < 7; i++)
		P[i] = S[9] + (i+1)*n*n/4;

	for(i = 0; i < n/2; i++){
		for(j = 0; j < n/2; j++){
			A00[j + i*n/2] = A[i*n + j];
			B00[j + i*n/2] = B[i*n + j];
			A01[j + i*n/2] = A[i*n + j + n/2];
			B01[j + i*n/2] = B[i*n + j + n/2];
			A10[j + i*n/2] = A[(i + n/2)*n + j];
			B10[j + i*n/2] = B[(i + n/2)*n + j];
			A11[j + i*n/2] = A[(i + n/2)*n + j + n/2];
			B11[j + i*n/2] = B[(i + n/2)*n + j + n/2];
		}
	}

	sub_mat(n/2, B01, B11, S[0]);
	add_mat(n/2, A00, A01, S[1]);
	add_mat(n/2, A10, A11, S[2]);
	sub_mat(n/2, B10, B00, S[3]);
	add_mat(n/2, A00, A11, S[4]);
	add_mat(n/2, B00, B11, S[5]);
	sub_mat(n/2, A01, A11, S[6]);
	add_mat(n/2, B10, B11, S[7]);
	sub_mat(n/2, A00, A10, S[8]);
	add_mat(n/2, B00, B01, S[9]);

	mul_stras_b(n/2, A00, S[0], P[0]);
	mul_stras_b(n/2, S[1], B11, P[1]);
	mul_stras_b(n/2, S[2], B00, P[2]);
	mul_stras_b(n/2, A11, S[3], P[3]);
	mul_stras_b(n/2, S[4],S[5], P[4]);
	mul_stras_b(n/2, S[6],S[7], P[5]);
	mul_stras_b(n/2, S[8],S[9], P[6]);

	for(i = 0; i < n/2; i++)
		for(j = 0; j < n/2; j++)
			C[i*n + j] = (P[4])[j + i*n/2] + (P[3])[j + i*n/2]
			        - (P[1])[j + i*n/2] + (P[5])[j + i*n/2];

	for(i = 0; i < n/2; i++)
		for(j = 0; j < n/2; j++)
			C[i*n + j + n/2] = (P[0])[j + i*n/2] + (P[1])[j + i*n/2];

	for(i = 0; i < n/2; i++)
		for(j = 0; j < n/2; j++)
			C[(i + n/2)*n + j] = (P[2])[j + i*n/2] + (P[3])[j + i*n/2];

	for(i = 0; i < n/2; i++)
		for(j = 0; j < n/2; j++)
			C[(i + n/2)*n + j + n/2] = (P[4])[j + i*n/2] + (P[0])[j + i*n/2]
			                    - (P[2])[j + i*n/2] - (P[6])[j + i*n/2];

	free(A00);
}

int main()
{
#define N 8
	int test[N][N]={
		{64,  2,  3, 61, 60,  6,  7, 57},
		{ 9, 55, 54, 12, 13, 51, 50, 16},
		{17, 47, 46, 20, 21, 43, 42, 24},
		{40, 26, 27, 37, 36, 30, 31, 33},
		{32, 34, 35, 29, 28, 38, 39, 25},
		{41, 23, 22, 44, 45, 19, 18, 48},
		{49, 15, 14, 52, 53, 11, 10, 56},
		{ 8, 58, 59,  5,  4, 62, 63,  1},
	};
	int result[N][N];
	print_array(N,N,test);
	printf("product:\n");
	mul_stras_b(N, &test[0][0], &test[0][0], &result[0][0]);
	print_array(N,N,result);
	return 0;
}
