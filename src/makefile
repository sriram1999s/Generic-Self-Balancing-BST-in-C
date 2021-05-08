a.out : $(ARGUMENT).o bst.o bst_iterator.o
	gcc $(ARGUMENT).o bst.o bst_iterator.o

$(ARGUMENT).o : bst.h bst_iterator.h test_files/$(ARGUMENT).c
	gcc -c test_files/$(ARGUMENT).c

bst.o : bst.h bst.c
	gcc -c bst.c

bst_iterator.o : bst.h bst_iterator.h bst_iterator.c
	gcc -c bst_iterator.c

debug:
	gcc test_files/$(ARGUMENT).c bst.c bst_iterator.c -g

clean:
	rm *.o a.out
