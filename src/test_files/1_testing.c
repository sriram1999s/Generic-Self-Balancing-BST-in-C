#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <assert.h>

#include "../bst.h"
#include "../bst_iterator.h"

bool less_int(const void * x, const void *y)
{
  return *(int*)x < *(int*)y;
}

void print_int(const void *ptr)
{
  printf("%d\t", *(int*)ptr);
}

int main()
{
  Bst t;
  init_bst(&t);

  int len = 8;
  int elts[] = {10, 5, 11, 7, 6, 9, 8, 11};

  for (int i=0; i<len; ++i) {
    bst_insert(&t, &elts[i], less_int);
  }

  inorder(&t, print_int);

  int temp1 = 5;
  int *ptr_temp1 = &temp1;
  bst_iterator it1 = find(&t, ptr_temp1, less_int);
  if(dereference(it1)) print_int(dereference(it1));
  printf("\n");

  int temp2 = 13;
  int *ptr_temp2 = &temp2;
  bst_iterator it2 = find(&t, ptr_temp2, less_int);
  assert(dereference(it2) == NULL);

  printf("size : %d\n", get_size(&t));
  bst_remove(&t, ptr_temp1, less_int);
  printf("Here\n");

  printf("size : %d\n", get_size(&t));
  inorder(&t, print_int);
  preorder(&t, print_int);
  postorder(&t, print_int);

  deallocate_bst(&t);
}
