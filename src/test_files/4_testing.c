#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <assert.h>

#include "../bst.h"
#include "../bst_iterator.h"

void print_double(const void *ptr)
{
	printf("%lf\t", *(double*)ptr);
}

bool less_double(const void *d1, const void *d2)
{
	return *(double*)d1 < *(double*)d2;
}

void disp(bst_iterator it1, bst_iterator it2)
{
	while (!equals(it1, it2)) {
		// if (!dereference(it1)) return;
		print_double(dereference(it1));
		it1 = get_next(it1);
	}
	printf("\n");
}

int main()
{
	Bst tree;
	init_bst(&tree);

	int len = 16;
	double elts[] = {1, 2, 3, 4, 0.3, -8.5, -7.6, -7.6, 110.5, -3, -3, 6.9, 4.20, 3.1, 2.2, 1.5};

	bst_array_insert(&tree, elts, len, less_double);

	inorder(&tree, print_double);
	printf("\n");

	disp(begin(&tree), end(&tree));

	for (int i=0; i<len; i += 3) {
		printf("Removing : ");
		print_double(&elts[i]);
		printf("\n");
		bst_remove(&tree, &elts[i], less_double);
	}  printf("\n");

	printf("After removal : ");
	inorder(&tree, print_double);
	printf("\n");

	bst_iterator it_begin = begin(&tree);
	bst_iterator it_end = end(&tree);

	bst_iterator it_find = find(&tree, &elts[1], less_double);
	printf("After find : ");
	print_double(dereference(it_find)); printf("\n");

	disp(it_begin, get_next(it_find));

	deallocate_bst(&tree);
}
