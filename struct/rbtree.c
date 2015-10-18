#include "sys.h"
#include "rbtree.h"

static void rb_subprint(rbnode *root, rbtree *tree)
{
	if(root == tree->nil)
		return;
	rb_subprint(root->lchild, tree);
	printf("%d\t", root->key);
	if(root->color == rb_red)
		printf("r\n");
	else
		printf("b\n");
	rb_subprint(root->rchild, tree);
}

void rb_print(rbtree *tree)
{
	printf("root:\n");
	printf("%d\t",tree->root->key);
	if(tree->root->color == rb_red)
		printf("r\n");
	else
		printf("b\n");
	printf("\n");
	rb_subprint(tree->root, tree);
}

void rb_init(rbtree *tree)
{
	tree->root = NULL;
	tree->nil = Malloc(sizeof(rbnode));
	tree->nil->color = rb_black;
	tree->size = 0;
}

static void rbsub_free(rbnode *root, rbnode *nil)
{
	if(root == nil)
		return;
	rbsub_free(root->lchild, nil);
	rbsub_free(root->rchild, nil);
	free(root);
}

void rb_free(rbtree *tree)
{
	rbsub_free(tree->root, tree->nil);
	free(tree->nil);
	tree->root = NULL;
	tree->nil = NULL;
}

rbnode *rb_min(rbnode *node, rbtree *tree)
{
	while(node->lchild != tree->nil)
		node = node->lchild;
	return node;
}

rbnode *rb_max(rbnode *node, rbtree *tree)
{
	while(node->rchild != tree->nil)
		node = node->rchild;
	return node;
}
			
/* rotate right */
rbnode *rb_rotate_r(rbnode *node, rbtree *tree)
{
	if(node->lchild == tree->nil)
		Error("cannot perform right rotate.\n");
	rbnode *lnode = node->lchild;
	lnode->parent = node->parent;
	node->parent = lnode;
	node->lchild = lnode->rchild;
	lnode->rchild = node;
	if(node->lchild != tree->nil)
		node->lchild->parent = node;
	if(node == tree->root)
		tree->root = lnode;
	else if(node == lnode->parent->lchild)
		lnode->parent->lchild = lnode;
	else
		lnode->parent->rchild = lnode;
	return lnode;
}

/* rotate left */
rbnode *rb_rotate_l(rbnode *node, rbtree *tree)
{
	if(node->rchild == tree->nil)
		Error("cannont perform left rotate");
	rbnode *rnode = node->rchild;
	rnode->parent = node->parent;
	node->parent  = rnode;
	node->rchild  = rnode->lchild;
	rnode->lchild = node;
	if(node->rchild != tree->nil)
		node->rchild->parent = node;
	if(node == tree->root)
		tree->root = rnode;
	else if(node == rnode->parent->lchild)
		rnode->parent->lchild = rnode;
	else
		rnode->parent->rchild = rnode;
	return rnode;
}



static void rb_insert_fix(rbnode *node, rbtree *tree)
{
	while(node->parent->color == rb_red){
		if(node->parent == node->parent->parent->lchild){
			if(node->parent->parent->rchild->color == rb_red){
				node->parent->color = rb_black;
				node->parent->parent->rchild->color = rb_black;
				node->parent->parent->color = rb_red;
				node = node->parent->parent;
			}
			else{
				if(node == node->parent->rchild){
					node = node->parent;
					rb_rotate_l(node, tree);
				}
				node->parent->color = rb_black;
				node->parent->parent->color = rb_red;
				rb_rotate_r(node->parent->parent, tree);
			}
		}
		else{
			if(node->parent->parent->lchild->color == rb_red){
				node->parent->color = rb_black;
				node->parent->parent->lchild->color = rb_black;
				node->parent->parent->color = rb_red;
				node = node->parent->parent;
			}
			else{
				if(node == node->parent->lchild){
					node = node->parent;
					rb_rotate_r(node, tree);
				}
				node->parent->color = rb_black;
				node->parent->parent->color = rb_red;
				rb_rotate_l(node->parent->parent, tree);
			}
		}
	}
	tree->root->color = rb_black;
}

rbnode *rb_insert(int key, rbtree *tree)
{
	rbnode *node = Malloc(sizeof(rbnode));
	node->key = key;
	node->lchild = tree->nil;
	node->rchild = tree->nil;
	if(tree->size == 0){
		node->color = rb_black;
		node->parent = tree->nil;
		tree->root = node;
		tree->size = 1;
		return node;
	}
	node->color = rb_red;
	rbnode *current = tree->root;
	rbnode *prev = current;
	while(current != tree->nil){
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
	tree->size ++;
	rb_insert_fix(node, tree);
	return node;
}

static void rb_trans(rbnode *old, rbnode *new, rbtree *tree)
{
	new->parent = old->parent;
	if(old == tree->root){
		tree->root = new;
		return;
	}
	if(old == old->parent->lchild)
		old->parent->lchild = new;
	else
		old->parent->rchild = new;
}



void rb_delete(rbnode *node, rbtree *tree)
{
	if(node == tree->nil)
		return;
	rbcolor color = node->color;
	rbnode *new;
	if(node->lchild == tree->nil){
		new = node->lchild;
		rb_trans(node, new, tree);
	}
	else if(node->rchild == tree->nil){
		new = node->rchild;
		rb_trans(node, new, tree);
	}
	else{
		new = rb_min(node->rchild, tree);
		color = new->color;
		if(new->parent != node){
			rb_trans(new, new->rchild, tree);
			new->rchild = node->rchild;
			new->rchild->parent = new;
		}
		rb_trans(node, new, tree);
		new->lchild = node->lchild;
		node->lchild->parent = new;
		new->color = color;
	}
	free(node);
}
