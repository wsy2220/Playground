#include <stdlib.h>
#include <limits.h>
#include <stdio.h>
#include <time.h>
#include <string.h>
#include <stdint.h>

void *Malloc(size_t size);
void *Calloc(size_t n, size_t size);
void Error(char *msg);
FILE *Fopen(char *path, char *mode);
void Fclose(FILE *fp);

