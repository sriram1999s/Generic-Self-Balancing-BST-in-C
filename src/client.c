#include<stdio.h>
#include<stdlib.h>

#include "bst.h"

void print_int(const void *ptr)
{
  printf("%d\t", *(int*)ptr);
}
int main()
{
  Bst t;
  init_bst(&t);
  int a = 10;
  int *ptr = &a;
  insert_bst(&t, ptr);
  inorder(&t, print_int);
}
