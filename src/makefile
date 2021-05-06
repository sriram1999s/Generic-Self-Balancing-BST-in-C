a.out : $(ARGUMENT).o bst.o
	gcc $(ARGUMENT).o bst.o

$(ARGUMENT).o : bst.h test_files/$(ARGUMENT).c
	gcc -c test_files/$(ARGUMENT).c

bst.o : bst.h bst.c
	gcc -c bst.c

debug:
	gcc test_files/$(ARGUMENT).c bst.c -g

clean:
	rm *.o a.out
