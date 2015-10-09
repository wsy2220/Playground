#include "sys.h"
#include "open_hash.h"
#include "hash_table.h"
#include "string.h"

void open_hash_alloc(open_table *otable)
{
	otable->table = Malloc(otable->entry_size * otable->size);
	size_t i;
	void *entry;
	for(i = 0; i < otable->size; i++){
		entry = otable_getobj(i, otable);
		otable->setstat(entry, entry_free);
	}
}

void open_hash_free(open_table *otable)
{
	size_t i;
	void *entry;
	if(otable->free_entry != NULL){
		for(i = 0; i < otable->size; i++){
			entry = otable_getobj(i, otable);
			if(otable->getstat(entry) == entry_allocated)
				otable->free_entry(entry);
		}
	}
	free(otable->table);
}

void *otable_getobj(size_t hash, open_table *otable)
{
	char *start = (char *)(otable->table);
	return start + otable->entry_size * hash;
}

void otable_cpyobj(void *dst, void *src, open_table *otable)
{
	memcpy(dst, src, otable->entry_size);
}


void open_hash_insert(open_table *otable, void *obj)
{
	size_t i, hash;
	void *entry;
	for(i = 0; i < otable->size; i++){
		hash = otable->hash(obj, i, otable);
		entry = otable_getobj(hash, otable);
		if(otable->getstat(entry) != entry_allocated){
			otable_cpyobj(entry, obj, otable);
			otable->setstat(entry, entry_allocated);
			break;
		}
	}
	if(i == otable->size){
		Error("hash table full!\n");
	}
}

void open_hash_delete(open_table *otable, void *entry)
{
	if(otable->free_entry != NULL)
		otable->free_entry(entry);
	otable->setstat(entry, entry_deleted);
}

void *open_hash_search(open_table *otable, void *obj)
{
	size_t i, hash;
	void *entry;
	for(i = 0; i < otable->size; i++){
		hash = otable->hash(obj, i, otable);
		entry = otable_getobj(hash, otable);
		if(otable->getstat(entry) == entry_allocated && 
		   otable->iseq(entry, obj)){
			return entry;
		}
		if(otable->getstat(entry) == entry_free){
			return NULL;
		}
	}
	return NULL;
}

size_t open_hash_str(void *str, size_t m, open_table *otable)
{
	unsigned long key = getkey_str(str);
	return div_hash(key + m, otable->size);
}

void open_hash_print(open_table *otable)
{
	size_t i;
	void *entry;
	for(i = 0; i < otable->size; i++){
		printf("%lu:\n", i);
		entry = otable_getobj(i, otable);
		if(otable->getstat(entry) == entry_allocated)
			otable->print(entry);
	}
}

