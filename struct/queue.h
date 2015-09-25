typedef struct {
	int *q;
	size_t head;
	size_t tail;
	size_t size;
} queue;

void queue_init(queue *qp, size_t size);
void queue_free(queue *qp);
void enqueue(queue *qp, int x);
int dequeue(queue *qp);
void enqueue_d(queue *qp, int x, int side);
int dequeue_d(queue *qp, int side);


enum {QUEUE_HEAD, QUEUE_TAIL};
