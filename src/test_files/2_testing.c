#include<stdio.h>
#include<stdlib.h>
#include<stdbool.h>

#include "../bst.h"

bool less_int(const void * x, const void *y)
{
  return *(int*)x < *(int*)y;
}

void print_int(const void *ptr)
{
  printf("%d\t", *(int*)ptr);
}

void disp(bst_iterator it1, bst_iterator it2)
{
  while (!equals(it1, it2)) {
    print_int(dereference(it1));
    it1 = get_next(it1);
  }
  printf("\n");
}

int main()
{
  Bst t;
  init_bst(&t);

  int len = 7;
  int elts[] = {10, 5, 2, 7, 6, 9, 8};

  for (int i=0; i<len; ++i) {
    insert_bst(&t, &elts[i], less_int);
  }

  inorder(&t, print_int);

  bst_iterator it_beg = begin(t);
  bst_iterator it_end = end(t);

  disp(it_beg, it_end);

  dealloc(&t);
}
