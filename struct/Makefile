CC = gcc
CFLAGS =  -Wall -Os -I../include -lm
out = test
obj = ../utils/utils.o ../utils/sys.o test.o stack.o queue.o lk_list.o tree.o hash_table.o


all: $(obj) 
	gcc $(CFLAGS) $(obj) -o $(out)

.PHONY: clean
clean: 
	-rm $(obj) $(out)
