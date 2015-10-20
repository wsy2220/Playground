#include "sys.h"
#include "rbtree.h"
#include "tree_print.h"

/* print tree at node, level is node's current level, return current line */
static size_t node_print(node_t *node, 
		               char (*buf)[WIDTH], 
					   size_t line, 
					   size_t level, 
					   tree_t *tree)
{
	size_t level_new = level + 1;
	size_t line_l, line_r;
	if(level * PAD >= WIDTH-PAD-1)
		return line + 1;
	if(node == NIL){
		buf[line][level * PAD] = X;
		buf[line][level * PAD + 1] = '\0';
		line ++;
		return line;
	}
	if(node->color == rb_red)
		sprintf(&buf[line][level * PAD],"%4dr---", node->key);
	else
		sprintf(&buf[line][level * PAD],"%4db---", node->key);
	line_l = node_print(node->lchild, buf, line, level_new, tree);
	line_r = node_print(node->rchild, buf, line_l, level_new, tree);
	size_t i;
	for(i = line + 1; i < line_l; i++)
		buf[i][level * PAD + 4] = V;
	buf[line_l][level * PAD + 4] = COR;
	for(i = 0; i < 3; i++)
		buf[line_l][level * PAD + 5 + i] = H;
	return line_r;
}

void tree_print(tree_t *tree)
{
	size_t line_total = tree->size * 2;
	size_t i;
	char (*buf)[WIDTH] = Malloc(WIDTH * line_total); /* get a screen buffer */
	memset(buf, ' ', WIDTH * line_total);
	node_print(tree->root, buf, 0, 0, tree);
	for(i = 0; i < line_total; i++){
		buf[i][WIDTH-1] = '\0';
		if(strlen(&buf[i][0]) < WIDTH - 1)
		printf("%s\n", &buf[i][0]);
	}
}

