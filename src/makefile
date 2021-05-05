a.out : client.o bst.o
	gcc client.o bst.o

client.o : bst.h client.c
	gcc -c client.c

bst.o : bst.h bst.c
	gcc -c bst.c

clean:
	rm *.o a.out
