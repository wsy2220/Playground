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

typedef struct lks_list{
	lk_element *start;  /* start as a sentinel */ 
	size_t size;
} lks_list;
void lks_init(lks_list *listp);
void lks_free(lks_list *listp);
void lks_insert(lks_list *listp, int key);
void lks_delete(lks_list *listp, lk_element *ele);
lk_element *lks_search(lks_list *listp, int key);
void lks_print(lks_list *listp);


void sglk_insert(lks_list *listp, int key);
void sglk_delete(lks_list *listp, lk_element *ele);
lk_element *sglk_search(lks_list *listp, int key);

void sglk_reverse(lks_list *listp);

/* xor list */
typedef struct xlk_element{
	int key;
	void *xaddr;
} xlk_element;
typedef struct xlk_list{
	xlk_element *start;
	xlk_element *prev;  /* real start->prev */
	size_t size;
} xlk_list;

void xlk_init(xlk_list *listp);
void xlk_free(xlk_list *listp);
void xlk_print(xlk_list *listp);
void xlk_insert(xlk_list *listp, int key);
void xlk_delete(xlk_list *listp, xlk_element *ele);
xlk_element *xlk_search(xlk_list *listp, int key);
void xlk_reverse(xlk_list *listp);
