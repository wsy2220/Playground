
typedef struct bin_node{
	int key;
	struct bin_node *parent;
	struct bin_node *lchild;
	struct bin_node *rchild;
} bin_node;

enum {BIN_LEFT, BIN_RIGHT};
bin_node *bin_tree_insert(bin_node *parent, int key, int parent_side, int child_side);
void bin_tree_free(bin_node *root);
void bin_tree_rprint(bin_node *root);
