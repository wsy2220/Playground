CC = gcc
CFLAGS =  -Wall -O2
obj = merge.o selection.o test.o  insertion.o bubble.o heap.o


all: $(obj) 
	gcc $(CFLAGS) $(obj) -o test 

.PHONY: clean
clean: 
	-rm $(obj) test
