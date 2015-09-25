typedef struct lk_element{
	int key;
	struct lk_element *prev;
	struct lk_element *next;
} lk_element;

typedef struct lk_list{
	lk_element *head;
	lk_element *start;     /* start of available memory */
	lk_element *end;       /* end   of available memory */
} lk_list;

void lk_init(lk_list *listp, size_t n);
void print_lk(lk_list *listp);
lk_element *lk_search(lk_list *listp, int x);
void lk_free(lk_list *listp);
void lk_insert(lk_list *listp, int key);
void lk_del(lk_list *listp, lk_element *ele);
