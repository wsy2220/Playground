#include "sys.h"
#include "tree.h"

bin_node *bin_tree_insert(bin_node *parent, int key, int parent_side, int child_side)
{
	bin_node *node = Malloc(sizeof(bin_node));
	node->parent = parent;
	node->key    = key;
	if(parent == NULL){
		node->lchild = NULL;
		node->rchild = NULL;
		return node;
	}
	if(child_side == BIN_LEFT){
		node->lchild = parent->lchild;
		node->rchild = NULL;
	}
	else{
		node->rchild = parent->rchild;
		node->lchild = NULL;
	}
	if(parent_side == BIN_LEFT)
		parent->lchild = node;
	else
		parent->rchild = node;
	return node;
}

void bin_tree_free(bin_node *root)
{
	if(root->lchild != NULL)
		bin_tree_free(root->lchild);
	if(root->rchild != NULL)
		bin_tree_free(root->rchild);
	free(root);
	root = NULL;
	return;
}

void bin_tree_rprint(bin_node *root)
{
	if(root == NULL)
		return;
	printf("%d\n", root->key);
	bin_tree_rprint(root->lchild);
	bin_tree_rprint(root->rchild);
}
