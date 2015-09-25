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


	





