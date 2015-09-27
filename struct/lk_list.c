#include "sys.h"
#include "lk_list.h"

void lk_init(lk_list *listp, size_t n)
{
	lk_element *ele;
	ele = malloc(sizeof(lk_element) * n);
	if(ele == NULL){
		fprintf(stderr, "malloc failed\n");
		exit(EXIT_FAILURE);
	}
	size_t i;
	for(i = 0; i < n; i++){
		ele[i].key = i;
		ele[i].prev = ele + i - 1;
		ele[i].next = ele + i + 1;
	}
	ele[0].prev = NULL;
	ele[n - 1].next = NULL;
	listp->head = ele;
	listp->start = ele;
	listp->end   = ele + n;
}

void lk_free(lk_list *listp)
{
	free(listp->start);
}

void print_lk(lk_list *listp)
{
	lk_element *ele = listp->head;
	do{
		printf("%d\n", ele->key);
		ele = ele->next;
	}while(ele->next != NULL);
	printf("%d\n", ele->key);
}

lk_element *lk_search(lk_list *listp, int x)
{
	lk_element *ele = listp->head;
	while(ele != NULL && ele->key != x)
		ele = ele->next;
	return ele;
}

/* insert key to the front */
void lk_insert(lk_list *listp, int key)
{
	lk_element *head = listp->head;
	lk_element *ele;
	if(head != NULL && head - 1 < listp->start){
		fprintf(stderr,"list full\n");
		exit(EXIT_FAILURE);
	}
	if(head == NULL){
		listp->head = ele = listp->start;
		ele->prev = ele->next = NULL;
	}
	else{
		ele = head - 1;
		listp->head = head->prev = ele;
		ele->next = head;
		ele->prev = NULL;
	}
	ele->key = key;
}

void lk_del(lk_list *listp, lk_element *ele)
{
	if(ele->prev != NULL)
		ele->prev->next = ele->next;
	else
		listp->head = ele->next;
	if(ele->next != NULL)
		ele->next->prev = ele->prev;
}

/* double linked list with sentinel */
void lks_init(lks_list *listp)
{
	lk_element *start;
	start = Malloc(sizeof(lk_element));
	/* init sentinel */
	start->key = 0;
	start->next = start->prev = start;
	listp->start = start;
	listp->size  = 1;
}

void lks_free(lks_list *listp)
{
	if(listp->size == 1){
		free(listp->start);
		return;
	}
	if(listp->size == 0)
		return;
	lk_element *ele = listp->start->next;
	while(ele != listp->start){
		free(ele->prev);
		ele = ele->next;
	}
}

/* insert key before sentinel */
void lks_insert(lks_list *listp, int key)
{
	lk_element *ele = Malloc(sizeof(lk_element));
	ele->prev = listp->start->prev;
	ele->next = listp->start;
	ele->key  = key;
	ele->prev->next = ele;
	listp->start->prev = ele;
	listp->size ++;
}

void lks_delete(lks_list *listp, lk_element *ele)
{
	ele->next->prev = ele->prev;
	ele->prev->next = ele->next;
	listp->size --;
	free(ele);
}

/* if not found, return NULL */
lk_element *lks_search(lks_list *listp, int key)
{
	lk_element *ele = listp->start->next;
	while(ele != listp->start && ele->key != key)
		ele = ele->next;
	if(ele->key == key && ele != listp->start)
		return ele;
	else
		return NULL;
}

void lks_union(lks_list *newp, lks_list *list1p, lks_list *list2p)
{
	newp->size = list1p->size + list2p->size;
	newp->start = list1p->start;
	list2p->start->prev = list1p->start;
	list1p->start->next = list2p->start;
}

void lks_print(lks_list *listp)
{
	printf("size: %lu\n", listp->size);
	if(listp->size == 0)
		return;
	printf("sentinel: %d, %p, %p, %p\n\n", listp->start->key, 
			listp->start, listp->start->prev, listp->start->next);
	lk_element *ele = listp->start->next;
	while(ele != listp->start){
		printf("%d, %p, %p, %p\n", ele->key, ele, ele->prev, ele->next);
		ele = ele->next;
	}
}

/* single circular list, just ingnore prev atrrib */
void sglk_insert(lks_list *listp, int key)
{
	lk_element *ele = Malloc(sizeof(lk_element));
	if(listp->size == 0){
		listp->start = ele;
		ele->key = key;
		ele->next = ele;
		listp->size = 1;
		return;
	}
	ele->key = key;
	ele->next = listp->start->next;
	listp->start->next = ele;
	listp->size ++;
}
void sglk_delete(lks_list *listp, lk_element *ele)
{
	lk_element *prev = listp->start;
	while(prev->next != ele)
		prev = prev->next;
	prev->next = ele->next;
	listp->size --;
	if(ele == listp->start)
		listp->start = ele->next;
	free(ele);
}

lk_element *sglk_search(lks_list *listp, int key)
{
	if(listp->size == 0)
		return NULL;
	lk_element *ele = listp->start;
	while(ele->key != key && ele->next != listp->start)
		ele = ele->next;
	if(ele->key == key)
		return ele;
	else
		return NULL;
}

void sglk_reverse(lks_list *listp)
{
	if(listp->size <= 1)
		return;
	lk_element *prev, *current = listp->start; 
	lk_element *next = listp->start->next;
	while(next != listp->start){
		prev = current;
		current = next;
		next = current->next;
		current->next = prev;
	}
	next->next = current;
}


/* xor list with two sentinels */
void xlk_init(xlk_list *listp)
{
	listp->start = Malloc(sizeof(xlk_element));
	xlk_element *ele = Malloc(sizeof(xlk_element));
	listp->size  = 2;
	listp->prev  = ele;
	listp->start->xaddr = 0;
	listp->start->key   = 0;
	ele->key = 0;
	ele->xaddr = 0;
}

#define XOR_ADDR(A, B) ((void *)((uintptr_t)(A) ^ (uintptr_t)(B)))
#define NEXT(CUR, P) XOR_ADDR((CUR)->xaddr,(P))
#define PREV(CUR, N) XOR_ADDR((CUR)->xaddr,(N))

void xlk_free(xlk_list *listp)
{
	if(listp->size == 1){
		free(listp->start);
		return;
	}
	xlk_element *current, *prev, *next;
	prev = listp->prev;
	current = listp->start;
	next = NEXT(current, prev);
	while(next != listp->start){
		free(current);
		prev = current;
		current = next;
		next = NEXT(current, prev);
	}
	free(current);
}

void xlk_print(xlk_list *listp)
{
	printf("size: %lu\n", listp->size);
	if(listp->size < 2)
		return;
	xlk_element *prev, *current, *next;
	prev = listp->prev;
	current = listp->start;
	next = NEXT(current, prev);
	printf("sentinel0: %d, %p, %p, %p\n", current->key, prev, current, next);
	printf("sentinel1: %d, %p, %p, %p\n", next->key, current, next,
			NEXT(next, current));
	prev = current;
	current = next;
	next = NEXT(current, prev);
	while(next != listp->start){
		printf("%d, %p, %p, %p\n", next->key, current, next, NEXT(next, current));
		prev = current;
		current = next;
		next = NEXT(next, prev);
	}
}

/* insert before sentinel */
void xlk_insert(xlk_list *listp, int key)
{
	xlk_element *ele = Malloc(sizeof(xlk_element));
	xlk_element *prev = listp->prev;
	ele->key = key;
	ele->xaddr =  XOR_ADDR(listp->prev ,listp->start);
	listp->start->xaddr = XOR_ADDR(ele ,NEXT(listp->start, listp->prev));
	listp->prev = ele;
	listp->size ++;
	prev->xaddr = XOR_ADDR(PREV(prev, listp->start), ele);
}

void xlk_delete(xlk_list *listp, xlk_element *ele)
{
	xlk_element *prev, *current, *next, *temp;
	prev = listp->start;
	current = NEXT(listp->start, listp->prev);
	next = NEXT(current, prev);
	while(next != ele){
		prev = current;
		current = next;
		next = NEXT(current, prev);
	}
	temp = NEXT(next, current);
	current->xaddr = XOR_ADDR(temp ,prev);
	temp->xaddr    = XOR_ADDR(NEXT(temp, next) ,current);
	if(temp == listp->start)
		listp->prev = current;
	listp->size --;
	free(next);
}

xlk_element *xlk_search(xlk_list *listp, int key)
{
	xlk_element *prev, *current, *next;
	prev = listp->start;
	current = NEXT(listp->start, listp->prev);
	next = NEXT(current, prev);
	while(next != listp->start && next->key != key){
		prev = current;
		current = next;
		next = NEXT(current, prev);
	}
	if(next->key == key && next != listp->start)
		return next;
	else
		return NULL;
}

void xlk_reverse(xlk_list *listp)
{
	xlk_element *s1 = listp->start;
	xlk_element *s2 = NEXT(listp->start, listp->prev);
	listp->start = s2;
	listp->prev = PREV(s2, s1);
}
