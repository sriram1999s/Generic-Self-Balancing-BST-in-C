#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <assert.h>

#include "../bst.h"
#include "../bst_iterator.h"

typedef struct Rect
{
	int l;
	int b;
} Rect;

void print_rect(const void *ptr)
{
	printf("l: %d b: %d\t", ((Rect*)ptr)->l, ((Rect*)ptr)->b);
}

bool less_rect(const void *r1, const void *r2)
{
	return ((Rect*)r1)->l * ((Rect*)r1)->b < ((Rect*)r2)->l * ((Rect*)r2)->b;
}

void disp(bst_iterator it1, bst_iterator it2)
{
	while (!equals(it1, it2)) {
		print_rect(dereference(it1));
		it1 = get_next(it1);
	}
	printf("\n");
}

int main()
{
	Bst tree;
	init_bst(&tree);

	int len = 6;
	Rect arr[] = {{1, 2}, {2, 3}, {0, 1}, {4, 5}, {1, 6}, {-2, 7}};

	bst_array_insert(&tree, arr, len, less_rect);

	inorder(&tree, print_rect); printf("\n");

	for (int i=0; i<len; i += 3) {
		printf("Removing : ");
		print_rect(&arr[i]);
		printf("\n");
		bst_remove(&tree, &arr[i], less_rect);
	}  printf("\n");

	inorder(&tree, print_rect);

	bst_iterator it = find(&tree, &arr[5], less_rect);
	printf("it: ");
	if (dereference(it)) print_rect(dereference(it)); printf("\n");

	disp(begin(&tree), end(&tree));

	deallocate_bst(&tree);
}
