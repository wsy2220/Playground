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

/* all print functions are in-order */
void bin_tree_rprint(bin_node *root)
{
	if(root == NULL)
		return;
	bin_tree_rprint(root->lchild);
	printf("%d\n", root->key);
	bin_tree_rprint(root->rchild);
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
			printf("%d\n", stack[top].node->key);
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
	prev = NULL;
	current = root;
	while(!(current == root && prev == root->rchild)){
		if(prev == current->parent){
			prev = current;
			if(current->lchild != NULL){
				current = current->lchild;
			}
			else if(current->rchild != NULL){
				printf("%d\n", current->key);
				current = current->rchild;
			}
			else{
				printf("%d\n", current->key);
				current = current->parent;
			}
			continue;
		}
		if(prev == current->lchild){
			printf("%d\n", current->key);
			prev = current;
			if(current->rchild != NULL){
				prev = current;
				current = current->rchild;
			}
			else{
				current = current->parent;
			}
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
