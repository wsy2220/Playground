#include "sys.h"
#include "stack.h"

void stack_init(stack *stp, size_t size)
{
	stp->s = malloc(sizeof(int) * size);
	if(stp->s == NULL){
		fprintf(stderr, "malloc failed\n");
		exit(EXIT_FAILURE);
	}
	stp->top  = -1;
	stp->size = size;
}

void stack_free(stack *stp)
{
	free(stp->s);
}

void stack_push(stack *stp, int t)
{
	if(stp->top == stp->size - 1){
		fprintf(stderr, "stack overflow\n");
		exit(EXIT_FAILURE);
	}
	stp->top += 1;
	(stp->s)[stp->top] = t;
}

int stack_pop(stack *stp)
{
	if(stp->top == -1){
		fprintf(stderr, "stack underflow\n");
		exit(EXIT_FAILURE);
	}
	stp->top -= 1;
	return (stp->s)[stp->top + 1];
}

void dstack_init(dstack *dstp, size_t size)
{
	dstp->s = malloc(sizeof(int) * size);
	if(dstp->s == NULL){
		fprintf(stderr, "malloc failed\n");
		exit(EXIT_FAILURE);
	}
	dstp->size = size;
	dstp->ltop = -1;
	dstp->htop = size;
}

void dstack_free(dstack *dstp)
{
	free(dstp->s);
}

void dstack_push(dstack *dstp, int x, int side)
{
	if(dstp->htop - dstp->ltop == 1){
		fprintf(stderr, "dstack overflow\n");
		exit(EXIT_FAILURE);
	}
	if(side == DSTACK_L){
		dstp->ltop ++;
		dstp->s[dstp->ltop] = x;
	}
	else if(side == DSTACK_H){
		dstp->htop --;
		dstp->s[dstp->htop] = x;
	}
}

int dstack_pop(dstack *dstp, int side)
{
	if(side == DSTACK_L && dstp->ltop == -1){
		fprintf(stderr, "lower dstack underflow\n");
		exit(EXIT_FAILURE);
	}
	if(side == DSTACK_H && dstp->htop == dstp->size){
		fprintf(stderr, "higher dstack underflow\n");
		exit(EXIT_FAILURE);
	}
	int ret;
	if(side == DSTACK_L){
		ret = dstp->s[dstp->ltop];
		dstp->ltop --;
	}
	else {
		ret = dstp->s[dstp->htop];
		dstp->htop ++;
	}
	return ret;
}
	
