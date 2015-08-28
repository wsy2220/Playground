CC = gcc
CFLAGS =  -Wall -g
obj = merge.o selection.o test.o  insertion.o


all: $(obj) 
	gcc $(CFLAGS) $(obj) -o test 

clean: 
	-rm $(obj) test
