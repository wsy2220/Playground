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

void *Calloc(size_t n, size_t size)
{
	void *ret = calloc(n, size);
	if(ret == NULL)
		Error("calloc failed\n");
	return ret;
}

FILE *Fopen(char *path, char *mode)
{
	FILE *fp = fopen(path, mode);
	if(fp==NULL)
		Error("cannot open file\n");
	return fp;
}

void Fclose(FILE *fp)
{
	int ret = fclose(fp);
	if(ret)
		Error("failed to close file\n");
}
