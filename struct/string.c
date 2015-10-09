#include "sys.h"
#include "string.h"
int iseq_str(void *obj1, void *obj2)
{
	string *str1 = obj1, *str2 = obj2;
	return !strcmp(str1->strp, str2->strp);
}

unsigned long getkey_str(string *str)
{
	unsigned long key = 0;
	size_t i;
	for(i = 0; i < str->length; i++)
		key += str->strp[i];
	return key;
}

void print_str(void *obj)
{
	string *str = obj;
	printf("%s", str->strp);
}

int getstat_str(void *obj)
{
	string *str = obj;
	return str->stat;
}

void setstat_str(void *obj, int stat)
{
	string *str = obj;
	str->stat = stat;
}

void free_str(void *obj)
{
	string *str = obj;
	free(str->strp);
}
