#include <stdio.h>
#define H 20


void hanoi(int n, int src, int dst, int res)
{
	if(n == 0)
		return;
	hanoi(n-1, src, res, dst);
	printf("%-8d\t%-8d\n", src, dst);
	hanoi(n-1, res, dst, src);
}

int main()
{
	hanoi(5, 0, 1, 2);
	return 0;
}
