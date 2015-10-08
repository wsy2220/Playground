typedef struct hash_list{
	void *obj;
	struct hash_list *prev;
	struct hash_list *next;
} hash_list;

typedef struct hash_table{
	hash_list **table;
	size_t size;
	size_t (*hash)(void *, struct hash_table *);
	int (*iseq)(void *, void *);
	void (*print)(void *);
	double frac;
} hash_table;

typedef struct string{
	char *strp;
	size_t length; /* excluding '\0' */
	size_t nline;
} string;

void *hash_table_search(hash_table *htable, void *obj);
void hash_table_alloc(hash_table *htable);
void hash_table_delete(hash_table *htable, void *obj);
void hash_table_destroy(hash_table *htable);
void hash_table_insert(hash_table *htable, void *obj);

int iseq_str(void *obj1, void *obj2);
size_t hash_str(void *obj, hash_table *htable);
void print_str(void *obj);
void hash_table_print(hash_table *htable);
