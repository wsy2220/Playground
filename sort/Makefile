CC = gcc
CFLAGS =  -Wall -Os
obj = merge.o selection.o test.o  insertion.o bubble.o heap.o qsort.o count.o


all: $(obj) 
	gcc $(CFLAGS) $(obj) -o test 

.PHONY: clean
clean: 
	-rm $(obj) test
