CC = gcc
CFLAGS =  -Wall -g
obj = merge.o selection.o test.o  insertion.o bubble.o


all: $(obj) 
	gcc $(CFLAGS) $(obj) -o test 

.PHONY: clean
clean: 
	-rm $(obj) test
