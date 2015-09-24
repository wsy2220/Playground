#include "sys.h"
#include "utils.h"
#define N 0x100

size_t water_part(int *A, size_t n, int mid)
{
	size_t i, j = 0;
	int temp;
	for(i = 0; i < n - 1; i++){
		if(A[i] < mid){
			temp = A[i];
			A[i] = A[j];	
			A[j] = temp;
			j++;
		}
		else if(A[i] == mid){
			A[i] = A[n-1];
			A[n-1] = mid;
			i--;
		}
	}
	A[n-1] = A[j];
	A[j] = mid;
	return j;
}

void water_sort(int *A, int *B, size_t n)
{
	if(n <= 1)
		return;
	size_t ind_mid = rand() % n;
	ind_mid = water_part(A, n, B[ind_mid]);
	water_part(B, n, A[ind_mid]);
	water_sort(A, B, ind_mid);
	water_sort(A + ind_mid + 1, B + ind_mid + 1, n - ind_mid -1);
}

		
	

int main()
{
	int A[N], B[N];
	size_t i;
	for(i = 0; i < N; i++)
		A[i] = B[i] = i;
	permute(A, N);
	permute(B, N);
	print_array(A, N);
	printf("\n");
	print_array(B, N);
	printf("\n");
	water_sort(A, B, N);
	print_array(A, N);
	printf("\n");
	print_array(B, N);
	printf("\n");
	return 0;
}

