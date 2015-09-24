#include "sys.h"

#define N 0x100
#define M 0x10

typedef int obj[M];
typedef struct {
	char *s;
	size_t size; /* excluding \0 */
} string;

char str_getchar(string *strp, size_t m)
{
	if(m >= strp->size)
		return 0;
	else
		return (strp->s)[m];
}

void str_sort_char(string **strpp, size_t n, size_t m)
{
	size_t i, j;
	string *temp;
	for(i = 1; i < n; i++)
		for(j = i; j > 0; j--){
			if(str_getchar(strpp[j], m) < str_getchar(strpp[j-1], m)){
				temp = strpp[j];
				strpp[j] = strpp[j-1];
				strpp[j-1] = temp;
			}
			else
				break;
		}
}

void str_sort(string **strpp, size_t n, size_t maxlen)
{
	size_t i;
	for(i = maxlen - 1; i != -1; i--)
		str_sort_char(strpp, n, i);
}

void print_str(string **strpp, size_t n)
{
	size_t i;
	for(i = 0; i < n; i++)
		printf("%s\n", strpp[i]->s);
}

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
	string str[N];
	string *strpp[N];
	char s[N][M];
	size_t i, j;
	for(i = 0; i < N; i++){
		for(j = 0; j < rand() % (M-1) + 1; j++)
			s[i][j] = rand() % 26 + 'A';
		str[i].size = j;
	}
	for(i = 0; i < N; i++){
		str[i].s = &s[i][0];
		strpp[i] = &str[i];
	}
	print_str(strpp, N);
	printf("\n");
	str_sort(strpp, N, M-1);
	print_str(strpp, N);
	printf("\n");
	return 0;
}
