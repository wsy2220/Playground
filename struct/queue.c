#include "sys.h"
#include "utils.h"
#include "queue.h"

void queue_init(queue *qp, size_t size)
{
	qp->q = malloc(sizeof(int) * size);
	if(qp->q == NULL){
		fprintf(stderr,"malloc failed\n");
		exit(EXIT_FAILURE);
	}
	qp->head = 0;
	qp->tail = 0;
	qp->size = size;
}

void queue_free(queue *qp)
{
	free(qp->q);
}

/* available space is size-1 */
void enqueue(queue *qp, int x)
{
	if((qp->tail == qp->size - 1 && qp->head == 0) ||
	   (qp->head - qp->tail == 1)){
		fprintf(stderr,"queue overflow\n");
		exit(EXIT_FAILURE);
	}
	qp->q[qp->tail] = x;
	if(qp->tail == qp->size - 1)
		qp->tail = 0;
	else
		qp->tail ++;
}

int dequeue(queue *qp)
{
	if(qp->tail == qp->head){
		fprintf(stderr,"queue underflow\n");
		exit(EXIT_FAILURE);
	}
	int ret = qp->q[qp->head];
	if(qp->head == qp->size - 1)
		qp->head = 0;
	else
		qp->head ++;
	return ret;
}

void enqueue_d(queue *qp, int x, int side)
{
	if((qp->tail == qp->size - 1 && qp->head == 0) ||
	   (qp->head - qp->tail == 1)){
		fprintf(stderr,"queue overflow\n");
		exit(EXIT_FAILURE);
	}
	if(side == QUEUE_HEAD){
		if(qp->head == 0)
			qp->head = qp->size - 1;
		else
			qp->head --;
		qp->q[qp->head] = x;
		return;
	}
	if(side == QUEUE_TAIL){
		qp->q[qp->tail] = x;
		if(qp->tail == qp->size - 1)
			qp->tail = 0;
		else
			qp->tail ++;
		return;
	}
}

int dequeue_d(queue *qp, int side)
{
	if(qp->tail == qp->head){
		fprintf(stderr,"queue underflow\n");
		exit(EXIT_FAILURE);
	}
	int ret;
	if(side == QUEUE_HEAD){
		ret = qp->q[qp->head];
		if(qp->head == qp->size - 1)
			qp->head = 0;
		else
			qp->head ++;
	}
	else{
		if(qp->tail == 0)
			qp->tail = qp->size - 1;
		else
			qp->tail --;
		ret = qp->q[qp->tail];
	}
	return ret;
}

