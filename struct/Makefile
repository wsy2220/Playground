CC = gcc
opt = -g
CFLAGS =  -Wall $(opt) -I../include -lm
out = test
obj = ../utils/utils.o ../utils/sys.o test.o stack.o queue.o lk_list.o tree.o hash_table.o open_hash.o string.o rbtree.o tree_print.o


all: $(obj) 
	gcc $(CFLAGS) $(obj) -o $(out)

.PHONY: clean
clean: 
	-rm $(obj) $(out)
