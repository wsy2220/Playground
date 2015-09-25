#include "sys.h"
#include "utils.h"
#include "stack.h"
#include "queue.h"
#include "lk_list.h"

#define N 0x20


void stack_test()
{
	stack st;
	stack_init(&st, N);
	size_t i;
	for(i = 0; i < N; i++)
		stack_push(&st, (int)i);
	for(i = 0; i < N; i++)
		printf("%d\n", stack_pop(&st));
	stack_free(&st);
}

void queue_test()
{
	queue q;
	queue_init(&q, N);
	size_t i;
	for(i = 0; i < 5; i++)
		enqueue_d(&q, i, QUEUE_HEAD);
	for(i = 0; i < 1; i++)
		printf("%d\n", dequeue_d(&q, QUEUE_HEAD));
	printf("\n");
	for(i = 0; i < 5; i++)
		enqueue_d(&q, i, QUEUE_TAIL);
	for(i = 0; i < 9; i++)
		printf("%d\n", dequeue_d(&q, QUEUE_HEAD));
	queue_free(&q);
}

void dstack_test()
{
	dstack dst;
	dstack_init(&dst, N);
	size_t i;
	for(i = 0; i < N/2; i++)
		dstack_push(&dst, (int)i, DSTACK_L);
	for(i = 0; i < N/2; i++)
		dstack_push(&dst, (int)i, DSTACK_H);
	for(i = 0; i < N/2; i++)
		printf("%d\n", dstack_pop(&dst, DSTACK_L));
	printf("\n");
	for(i = 0; i < N/2; i++)
		printf("%d\n", dstack_pop(&dst, DSTACK_H));
	dstack_free(&dst);
}

void lk_list_test()
{
	lk_list list;
	lk_init(&list, N);
	print_lk(&list);
	printf("\n");
	lk_del(&list, list.head);
	print_lk(&list);
	printf("\n");
	lk_insert(&list, 100);
	print_lk(&list);
	printf("\n");
	lk_free(&list);
}

int main()
{
	lk_list_test();
	return 0;
}
