#include <stdio.h>
#include <stdlib.h>
#include <limits.h>

#define MAGIC INT_MIN
#define MAX(a,b) ((a) > (b) ? (a) : (b))

int rod_td(int *price, int *table, int length)
{
	if(table[length] != MAGIC){
		return table[length];
	}
	int price_max = INT_MIN;
	int i;
	for(i = 1; i <= length; i++){
		price_max = MAX(price_max, price[i] + rod_td(price, table, length - i));
	}
	table[length] = price_max;
	return price_max;
}

int rod_bu(int *price, int *table, int *cut, int length)
{
	if(length == 0)
		return price[0];
	int i, j;
	table[0] = 0;
	for(i = 1; i <= length; i++){
		int price_max = INT_MIN;
		for(j = 1; j <= i; j++){
			if(price_max < price[j] + table[i - j]){
				price_max = price[j] + table[i - j];
				cut[i] = j;
			}
		}
		table[i] = price_max;
	}
	return table[length];
}
		

#define LENGTH 10
#define TABLEN 11
void rod_test()
{
	int price[] = {
		0, 1, 5, 8, 9, 10, 17, 17, 20, 24, 30};
	int table[TABLEN], i;
	int cut[TABLEN];
	table[0] = 0;
	cut[0] = 0;
	for(i = 1; i < TABLEN; i++){
		table[i] = MAGIC;
	}
	int result = rod_bu(price, table, cut, LENGTH);
	for(i = 0; i < TABLEN; i++){
		printf("%d\t%d\n", table[i], cut[i]);
	}
	printf("%d\n", result);
	i = LENGTH;
	while(i > 0){
		printf("%d\n", cut[i]);
		i = i - cut[i];
	}
}

int main()
{
	rod_test();
	return 0;
}

