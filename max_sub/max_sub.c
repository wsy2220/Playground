#include <stdio.h>
#include <stdlib.h>
#include <limits.h>

typedef struct {
	ssize_t lower;
	ssize_t mid;
	ssize_t upper;
} range;


int max_cross(int *A, range *input, range *output)
{
	int sum_low = INT_MIN;
	int sum_high = INT_MIN;
	int sum = 0;
	ssize_t i;
	for(i = input->mid; i >= input->lower; i--){
		sum += A[i];
		if(sum > sum_low){
			sum_low = sum;
			output->lower = i;
		}
	}
	sum = 0;
	for(i = input->mid + 1; i <= input->upper; i++){
		sum += A[i];
		if(sum > sum_high){
			sum_high = sum;
			output->upper = i;
		}
	}
	return sum_low + sum_high;
}

/* recurrsive solution */
int max_sub(int *A, range *input, range *output)
{
	if(input->lower == input->upper){
		output->lower = output->upper = input->lower;
		return A[input->lower];
	}
	range left_in = {input->lower, 
		             (input->mid + input->lower) / 2,
					 input->mid};
	range right_in = {input->mid + 1,
		              (input->mid + 1 + input->upper) / 2,
					  input->upper};
	range cross_in = {input->lower,
		              input->mid,
					  input->upper};
	range left_out, cross_out, right_out;
	int left_max, cross_max, right_max;
	left_max  = max_sub(A, &left_in, &left_out);
	cross_max = max_cross(A, &cross_in, &cross_out);
	right_max = max_sub(A, &right_in, &right_out);
	if(left_max >= cross_max && left_max >= right_max){
		output->lower = left_out.lower;
		output->upper = left_out.upper;
		return left_max;
	}
	else if(cross_max >= left_max && cross_max >= right_max){
		output->lower = cross_out.lower;
		output->upper = cross_out.upper;
		return cross_max;
	}
	else{
		output->lower = right_out.lower;
		output->upper = right_out.upper;
		return right_max;
	}
}

/* brute force solution */
int max_sub_b(int *A, range *input, range *output)
{
	ssize_t i, j;
	int sum, max = INT_MIN;
	for(i = input->lower; i <= input->upper; i++){
		sum = 0;
		for(j = i; j <= input->upper; j++){
			sum += A[j];
			if(sum > max){
				max = sum;
				output->lower = i;
				output->upper = j;
			}
		}
	}
	return max;
}

/* linear-time solution */
int max_sub_c(int *A, range *input, range *output)
{
	ssize_t i, lower = input->lower, upper = input->lower;
	int sum = A[input->lower], max = sum; 
	for(i = input->lower + 1; i <= input->upper; i++){
		if(sum > 0){
			upper = i;
			sum += A[i];
		}
		else{
			lower = upper = i;
			sum = A[i];
		}
		if(sum > max){
			max = sum;
			output->lower = lower;
			output->upper = upper;
		}
	}
	return max;
}

int main()
{
	//int test[10] = {2,1,1,-3,1,1,-3,1,2,1};
	int test[16] = {13,-3,-25,20,-3,-16,-23,18,20,-7,12,-5,-22,15,-4,7};
	int max;
	range output, input = {0, sizeof(test)/sizeof(int)/2, sizeof(test)/sizeof(int)-1};
	max = max_sub_c(test, &input, &output);
	printf("max\tlower\tupper\n");
	printf("%d\t%lu\t%lu\n", max, output.lower, output.upper);
	return 0;
}

