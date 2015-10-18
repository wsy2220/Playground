typedef enum rbcolor {rb_red, rb_black} rbcolor;
typedef struct rbnode{
	int key;
	rbcolor color;
	struct rbnode *parent;
	struct rbnode *lchild;
	struct rbnode *rchild;
} rbnode;

typedef struct rbtree {
	rbnode *root;
	rbnode *nil;
	size_t size;
} rbtree;

rbnode *rb_insert(int key, rbtree *tree);
rbnode *rb_rotate_l(rbnode *node, rbtree *tree);
rbnode *rb_rotate_r(rbnode *node, rbtree *tree);
void rb_free(rbtree *tree);
void rb_init(rbtree *tree);
void rb_print(rbtree *tree);
rbnode *rb_min(rbnode *node, rbtree *tree);
rbnode *rb_max(rbnode *node, rbtree *tree);
void rb_delete(rbnode *node, rbtree *tree);
