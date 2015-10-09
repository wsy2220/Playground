enum entry_stat{entry_free, entry_allocated, entry_deleted};
typedef struct open_table{
	void *table;
	size_t size;
	size_t entry_size;
	size_t (*hash)(void *obj, size_t m, struct open_table *otable);
	enum entry_stat (*getstat)(void *entry);
	void (*setstat)(void *entry, enum entry_stat);
	int (*iseq)(void *entry, void *obj);
	void (*print)(void *obj);
	void (*free_entry)(void *entry); /*free resources related to the entry */
} open_table;

void open_hash_alloc(open_table *otable);
void open_hash_free(open_table *otable);
void open_hash_insert(open_table *otable, void *obj);
void open_hash_delete(open_table *otable, void *entry);
void *open_hash_search(open_table *otable, void *obj);
void *otable_getobj(size_t hash, open_table *otable);
void otable_cpyobj(void *dst, void *src, open_table *otable);
size_t open_hash_str(void *str, size_t m, open_table *otable);
void open_hash_print(open_table *otable);
