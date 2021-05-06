a.out : client.o bst.o
	gcc client.o bst.o

client.o : bst.h client.c
	gcc -c client.c

bst.o : bst.h bst.c
	gcc -c bst.c

debug:
	gcc client.c bst.c -g

clean:
	rm *.o a.out
