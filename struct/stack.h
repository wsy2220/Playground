typedef struct {
	int *s;
	size_t top;
	size_t size;
} stack;

void stack_push(stack *stp, int t);
int stack_pop(stack *stp);
void stack_init(stack *stp, size_t size);
void stack_free(stack *stp);

typedef struct{
	int *s;
	size_t size;
	size_t ltop;
	size_t htop;
} dstack;


enum{ DSTACK_L, DSTACK_H};
void dstack_init(dstack *dstp, size_t size);
void dstack_free(dstack *dstp);
void dstack_push(dstack *dstp, int x, int side);
int dstack_pop(dstack *dstp, int side);
