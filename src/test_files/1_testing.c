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

  int temp1 = 5;
  int *ptr_temp1 = &temp1;
  find(&t, ptr_temp1, less_int);

  int temp2 = 13;
  int *ptr_temp2 = &temp2;
  find(&t, ptr_temp2, less_int);

  remove_bst(&t, ptr_temp1, less_int);
  inorder(&t, print_int);

  dealloc(&t);
}
