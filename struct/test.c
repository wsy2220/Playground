#include "sys.h"
#include "utils.h"
#include "stack.h"
#include "queue.h"
#include "lk_list.h"
#include "tree.h"
#include "hash_table.h"
#include "open_hash.h"
#include "string.h"

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

void lks_list_test()
{
	lks_list list;
	lks_init(&list);
	size_t i;
	for(i = 0; i < N; i++)
		lks_insert(&list, (int)i);
	lks_print(&list);
	printf("\n");
	sglk_reverse(&list);
	lks_print(&list);
	printf("\n");
	lks_free(&list);
}

void xlk_list_test()
{
	xlk_list list;
	xlk_element *ele;
	int r;
	xlk_init(&list);
	size_t i;
	for(i = 0; i < N; i++)
		xlk_insert(&list, (int)i);
	xlk_print(&list);
	for(i = 0; i < N; i++){
		r = rand() % N;
		ele = xlk_search(&list, r);
		if(ele != NULL){
			printf("%d(%d) found\n", r, ele->key);
			xlk_delete(&list, ele);
		}
		else
			printf("%d not found\n", r);
	}

	xlk_print(&list);
	printf("\n");
	xlk_reverse(&list);
	xlk_print(&list);
	xlk_free(&list);
}

void bin_tree_test()
{
	bin_node *p[N] ;
	size_t i;
	p[0] = malloc(sizeof(bin_node));
	p[0]->key = 0;
	p[0]->parent = NULL;
	for(i = 1; i < N; i++){
		p[i] = malloc(sizeof(bin_node));
		p[i]->key = i;
		p[i]->parent = p[(i-1)/2];
		p[i]->lchild = p[i]->rchild = NULL;
		if(i % 2 == 1)
			p[i]->parent->lchild = p[i];
		else
			p[i]->parent->rchild = p[i];
	}
	bin_tree_llprint(p[0]);
}

void sib_tree_test()
{
	sib_node *p[N];
	size_t i;
	for(i = 0; i < N; i++)
		p[i] = malloc(sizeof(sib_node));
	p[0]->key = 0;
	p[0]->parent = NULL;
	p[0]->sibling = NULL;
	for(i = 1; i < N; i++){
		p[i]->key = i;
		p[i]->parent = p[(i-1)/4];
		p[i]->lchild = NULL;
		if(i % 4 == 1){
			p[i]->parent->lchild = p[i];
			p[i]->sibling = (i >= N-1) ? NULL : p[i+1];
		}
		else if(i % 4 == 0){
			p[i]->sibling = NULL;
		}
		else{
			p[i]->sibling = (i >= N-1) ? NULL : p[i+1];
		}
	}
	for(i = 0; i < N; i++)
		printf("%d  %p  %p  %p\n",p[i]->key, p[i]->parent, p[i]->lchild, p[i]->sibling);
	sib_tree_print(p[0]);
}

#define MAX_LEN 0x1000
#define MAX_LINE 0x1000
#define PATH "/home/wsy/src/git/git.c"
void hash_table_test()
{
	hash_table ht;
	ht.size = 569;
	ht.hash = hash_str;
	ht.iseq = iseq_str;
	ht.frac = 0.618;
	ht.print = print_str;
	hash_table_alloc(&ht);
	FILE *fp = Fopen(PATH, "r");
	string *strpool[MAX_LINE], *str;
	size_t i, line_total;
	for(i = 0; i < MAX_LINE; i++){
		str = malloc(MAX_LEN + sizeof(string));
		strpool[i] = str;
		str->strp = (char *)str + sizeof(string);
		str->nline = i + 1;
		if(fgets(str->strp, MAX_LEN, fp) != NULL){
			str->length = strlen(str->strp);
			hash_table_insert(&ht, strpool[i]);
		}
		else{
			strpool[i] = NULL;
			free(str);
			break;
		}
	}
	line_total = i;
	string sample, *result;
	sample.strp = "{\n";
	sample.length = strlen(sample.strp);
	result = hash_table_search(&ht, &sample);
	//hash_table_print(&ht);
	if(result != NULL)
		printf("%lu\t%s",result->nline, result->strp);
	else
		printf("not found\n");
	hash_table_destroy(&ht);
	for(i = 0; i < line_total; i++)
		free(strpool[i]);
	Fclose(fp);
}

void open_hash_test()
{
	open_table ot;
	ot.size = MAX_LINE;
	ot.entry_size = sizeof(string);
	ot.hash = open_hash_str;
	ot.getstat = getstat_str;
	ot.setstat = setstat_str;
	ot.iseq = iseq_str;
	ot.print = print_str;
	ot.free_entry = free_str;
	open_hash_alloc(&ot);
	FILE *fp = Fopen(PATH, "r");
	string current, *result;
	size_t i;
	for(i = 0; i < MAX_LINE; i++){
		char *s = Malloc(MAX_LEN);
		if(fgets(s, MAX_LEN, fp) != NULL){
			current.length = strlen(s);
			current.strp = s;
			current.nline = i + 1;
			open_hash_insert(&ot, &current);
		}
		else{
			free(s);
			break;
		}
	}
	//open_hash_print(&ot);
	current.strp = "int main(int argc, char **av)\n";
	current.length = strlen(current.strp);
	result = open_hash_search(&ot, &current);
	if(result != NULL)
		printf("%lu\t%s",result->nline, result->strp);
	else
		printf("not found\n");
	open_hash_free(&ot);
}

int main()
{
	open_hash_test();
	return 0;
}
