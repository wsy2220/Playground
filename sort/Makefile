CC = gcc
CFLAGS =  -Wall -Os -I../include
obj = merge.o selection.o test.o  insertion.o bubble.o heap.o qsort.o count.o ../utils/utils.o rselect.o


all: $(obj) 
	gcc $(CFLAGS) $(obj) -o test 

.PHONY: clean
clean: 
	-rm $(obj) test
