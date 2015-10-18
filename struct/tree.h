
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

bin_node *bs_tree_insert(bin_node **rootp, int key);
bin_node *bs_tree_rinsert(bin_node **rootp, int key);
bin_node *bs_tree_max(bin_node *root);
bin_node *bs_tree_min(bin_node *root);
bin_node *bs_tree_pred(bin_node *root);
bin_node *bs_tree_rmax(bin_node *root);
bin_node *bs_tree_rmin(bin_node *root);
bin_node *bs_tree_rsearch(bin_node *root, int key);
bin_node *bs_tree_search(bin_node *root, int key);
bin_node *bs_tree_succ(bin_node *root);
void bs_tree_revert(bin_node *root);
void bs_tree_delete(bin_node **rootp, bin_node *node);
void bs_tree_del(bin_node **rootp, bin_node *node);
