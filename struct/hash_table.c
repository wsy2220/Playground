#include "sys.h"
#include <math.h>
#include "hash_table.h"

size_t div_hash(unsigned long key, size_t size);
size_t mul_hash(unsigned long key, size_t size, double frac);


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

size_t hash_str(void *obj, hash_table *htable)
{
	string *str = obj;
	unsigned long key = getkey_str(str);
	return div_hash(key, htable->size);
}

void print_str(void *obj)
{
	string *str = obj;
	printf("%s", str->strp);
}

void hash_table_alloc(hash_table *htable)
{
	htable->table = Calloc(htable->size, sizeof(hash_list *));
}

size_t div_hash(unsigned long key, size_t size)
{
	return key % size;
}

size_t mul_hash(unsigned long key, size_t size, double frac)
{
	return (size_t)(fmod(key * frac, 1) * size);
}

void hash_list_insert(hash_list **entryp, void *obj)
{
	hash_list *list = Malloc(sizeof(hash_list));
	list->prev = NULL;
	list->next = *entryp;
	list->obj = obj;
	if(*entryp != NULL)
		(*entryp)->prev = list;
	*entryp = list;
	
}

void hash_list_delete(hash_list **entryp, hash_list *list)
{
	if(*entryp == list){
		*entryp = list->next;
		list->next->prev = NULL;
	}
	else if (list->next == NULL){
		list->prev->next = NULL;
	}
	else{
		list->prev->next = list->next;
		list->next->prev = list->prev;
	}
	free(list);
}

hash_list *hash_list_search(hash_list **entryp, int (*iseq)(void *, void *), void *obj)
{
	hash_list *current = *entryp;
	while(current != NULL && !iseq(current->obj, obj))
		current = current->next;
	return current;
}

void hash_list_print(hash_list **entryp, void (*print)(void *))
{
	hash_list *current = *entryp;
	while(current != NULL){
		print(current->obj);
		current = current->next;
	}
}

void hash_list_free(hash_list **entryp)
{
	hash_list *current = *entryp;
	hash_list *temp; 
	while(current != NULL){
		temp = current->next;
		free(current);
		current = temp;
	}
	*entryp = NULL;
}


void hash_table_insert(hash_table *htable, void *obj) 
{
	hash_list **entryp = htable->table + htable->hash(obj, htable);
	hash_list_insert(entryp, obj);
}

void hash_table_delete(hash_table *htable, void *obj)
{
	hash_list **entryp = htable->table + htable->hash(obj, htable);
	hash_list *list = hash_list_search(entryp, htable->iseq, obj);
	hash_list_delete(entryp, list);
}

void *hash_table_search(hash_table *htable, void *obj)
{
	hash_list **entryp = htable->table + htable->hash(obj, htable);
	hash_list *result;
	result = hash_list_search(entryp, htable->iseq, obj);
	if(result != NULL)
		return result->obj;
	else
		return NULL;
}

void hash_table_destroy(hash_table *htable)
{
	size_t i;
	for(i = 0; i < htable->size; i++)
		hash_list_free(htable->table + i);
	htable->table = NULL;
}

void hash_table_print(hash_table *htable)
{
	size_t i;
	for(i = 0; i < htable->size; i++){
		printf("%lu:\n",i);
		hash_list_print(htable->table + i, htable->print);
	}
}

