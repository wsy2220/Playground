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

bin_node *bs_tree_search(bin_node *root, int key)
{
	bin_node *current = root;
	while(current != NULL && current->key != key){
		if(current->key > key)
			current = current->lchild;
		else
			current = current->rchild;
	}
	return current;
}

bin_node *bs_tree_rsearch(bin_node *root, int key)
{
	if(root == NULL || root->key == key)
		return root;
	if(root->key > key)
		return bs_tree_rsearch(root->lchild, key);
	else
		return bs_tree_rsearch(root->rchild, key);
}

bin_node *bs_tree_max(bin_node *root)
{
	bin_node *current = root;
	while(current->rchild != NULL)
		current = current->rchild;
	return current;
}

bin_node *bs_tree_rmin(bin_node *root)
{
	if(root->lchild == NULL)
		return root;
	else
		return bs_tree_rmin(root->lchild);
}

bin_node *bs_tree_rmax(bin_node *root)
{
	if(root -> rchild == NULL)
		return root;
	else
		return bs_tree_rmax(root->rchild);
}

bin_node *bs_tree_min(bin_node *root)
{
	bin_node *current = root;
	while(current->lchild != NULL)
		current = current->lchild;
	return current;
}

bin_node *bs_tree_pred(bin_node *node)
{
	if(node->lchild != NULL)
		return bs_tree_max(node->lchild);
	bin_node *current = node;
	while(current->parent != NULL && current != current->parent->rchild)
		current = current->parent;
	return current->parent;
}

bin_node *bs_tree_succ(bin_node *node)
{
	if(node->rchild != NULL)
		return bs_tree_min(node->rchild);
	bin_node *current = node;
	while(current->parent != NULL && current != current->parent->lchild)
		current = current->parent;
	return current->parent;
}

void bs_tree_revert(bin_node *root)
{
	if(root == NULL)
		return;
	bin_node *temp;
	temp = root->lchild;
	root->lchild = root->rchild;
	root->rchild = temp;
	bs_tree_revert(root->lchild);
	bs_tree_revert(root->rchild);
}

bin_node *bs_tree_insert(bin_node **rootp, int key)
{
	bin_node *node = Malloc(sizeof(bin_node));
	node->key = key;
	node->lchild = node->rchild = NULL;
	if(*rootp == NULL){
		node->parent = NULL;
		*rootp = node;
		return node;
	}
	bin_node *prev, *current = *rootp;
	while(current != NULL){
		prev = current;
		if(current->key > key)
			current = current->lchild;
		else
			current = current->rchild;
	}
	node->parent = prev;
	if(prev->key > key)
		prev->lchild = node;
	else
		prev->rchild = node;
	return node;
}

bin_node *bs_tree_rinsert(bin_node **rootp, int key)
{
	if(*rootp == NULL){
		*rootp = Malloc(sizeof(bin_node));
		(*rootp)->parent = NULL;
		(*rootp)->lchild = (*rootp)->rchild = NULL;
		(*rootp)->key = key;
		return *rootp;
	}
	bin_node *current = *rootp;
	if(current->key > key && current->lchild != NULL)
		return bs_tree_rinsert(&(current->lchild), key);
	if(current->key <= key && current->rchild != NULL)
		return bs_tree_rinsert(&(current->rchild), key);
	bin_node *new;
	new = Malloc(sizeof(bin_node));
	new->key = key;
	new->lchild = new->rchild = NULL;
	new->parent = current;
	if(current->key > key)
		current->lchild = new;
	else
		current->rchild = new;
	return new;
}


void bs_tree_delete(bin_node **rootp, bin_node *node)
{
	bin_node *replace;
	if(node->lchild == NULL)
		replace = node->rchild;
	else if(node->rchild == NULL)
		replace = node->lchild;
	else{
		replace = bs_tree_succ(node);
		if(replace != node->rchild){
			replace->parent->lchild = replace->rchild;
			if(replace->rchild != NULL)
				replace->rchild->parent = replace->parent;
			replace->rchild = node->rchild;
			replace->rchild->parent = replace;
		}
		replace->lchild = node->lchild;
		replace->lchild->parent = replace;
	}
	if(node == *rootp)
		*rootp = replace;
	else if(node == node->parent->lchild)
		node->parent->lchild = replace;
	else
		node->parent->rchild = replace;
	if(replace != NULL)
		replace->parent = node->parent;
	free(node);
}

static void bs_tree_trans(bin_node **rootp, bin_node *old, bin_node *new)
{
	if(new != NULL)
		new->parent = old->parent;
	if(*rootp == old){
		*rootp = new;
		return;
	}
	if(old == old->parent->lchild)
		old->parent->lchild = new;
	else
		old->parent->rchild = new;
}

void bs_tree_del(bin_node **rootp, bin_node *node)
{
	if(node->lchild == NULL)
		bs_tree_trans(rootp, node, node->rchild);
	else if(node->rchild == NULL)
		bs_tree_trans(rootp, node, node->lchild);
	else{
		bin_node *new = bs_tree_min(node->rchild);
		if(new->parent != node){
			bs_tree_trans(rootp, new, new->rchild);
			new->rchild = node->rchild;
			new->rchild->parent = new;
		}
		bs_tree_trans(rootp, node, new);
		new->lchild = node->lchild;
		new->lchild->parent = new;
	}
	free(node);
}
