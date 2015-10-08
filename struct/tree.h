
typedef struct bin_node{
	int key;
	struct bin_node *parent;
	struct bin_node *lchild;
	struct bin_node *rchild;
} bin_node;

typedef struct sib_node{
	int key;
	struct sib_node *parent;
	struct sib_node *lchild;
	struct sib_node *sibling;
} sib_node;

enum {BIN_LEFT, BIN_RIGHT};
bin_node *bin_tree_insert(bin_node *parent, int key, int parent_side, int child_side);
void bin_tree_free(bin_node *root);
void bin_tree_rprint(bin_node *root);
void bin_tree_lprint(bin_node *root);
void bin_tree_llprint(bin_node *root);
void sib_tree_print(sib_node *root);
