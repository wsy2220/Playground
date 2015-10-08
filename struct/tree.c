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
	bin_tree_rprint(root->lchild);
	bin_tree_rprint(root->rchild);
	printf("%d\n", root->key);
}

#define ST_SIZE 0x100
void bin_tree_lprint(bin_node *root)
{
	struct {
		bin_node *node;
		int lprinted;
		int rprinted;
	} stack[ST_SIZE];
	size_t top = 0;
	stack[top].node = root;
	stack[top].lprinted = 0;
	stack[top].rprinted = 0;
	while(top != -1){
		if(stack[top].node == NULL){
			top --;
			continue;
		}
		if(stack[top].lprinted && stack[top].rprinted){
			printf("%d\n", stack[top].node->key);
			top --;
			continue;
		}
		if(!stack[top].lprinted && !stack[top].rprinted){
			stack[top].lprinted = 1;
			top ++;
			stack[top].node = stack[top-1].node->lchild;
			stack[top].lprinted = 0;
			stack[top].rprinted = 0;
			continue;
		}
		if(stack[top].lprinted && !stack[top].rprinted){
			stack[top].rprinted = 1;
			top ++;
			stack[top].node = stack[top-1].node->rchild;
			stack[top].lprinted = 0;
			stack[top].rprinted = 0;
			continue;
		}
	}
}


void bin_tree_llprint(bin_node *root)
{
	bin_node *prev, *current;
	prev = root;
	printf("%d\n", root->key);
	current = root->lchild;
	while(current != root || prev != root->rchild){
		if(current == NULL){
			current = prev;
			prev = NULL;
			continue;
		}
		if(prev == current->parent){
			printf("%d\n", current->key);
			prev = current;
			current = current->lchild;
			continue;
		}
		if(prev == current->lchild && current->lchild != current->rchild){
			prev = current;
			current = current->rchild;
			continue;
		}
		if(prev == current->rchild){
			prev = current;
			current = current->parent;
			continue;
		}
	}
}

void sib_tree_print(sib_node *root)
{
	sib_node *sib = root;
	while(sib != NULL){
		printf("%d\n",sib->key);
		sib_tree_print(sib->lchild);
		sib = sib->sibling;
	}
}
