#include "sys.h"

void Error(char *msg)
{
	fprintf(stderr, msg);
	exit(EXIT_FAILURE);
}

void *Malloc(size_t size)
{
	void *ret = malloc(size);
	if(ret == NULL)
		Error("malloc failed\n");
	return ret;
}

