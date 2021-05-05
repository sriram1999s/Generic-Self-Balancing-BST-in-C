#include<stdio.h>
#include<stdlib.h>
#include<stdbool.h>

#include "bst.h"

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
  int a1 = 10;
  int *ptr1 = &a1;
  int a2 = 5;
  int *ptr2 = &a2;
  int a3 = 2;
  int *ptr3 = &a3;
  int a4 = 9;
  int *ptr4 = &a4;
  int a5 = 6;
  int *ptr5 = &a5;

  insert_bst(&t, ptr1, less_int);
  insert_bst(&t, ptr2, less_int);
  insert_bst(&t, ptr3, less_int);
  insert_bst(&t, ptr4, less_int);
  insert_bst(&t, ptr5, less_int);

  inorder(&t, print_int);

  int temp1 = 5;
  int *ptr_temp1 = &temp1;
  find(&t, ptr_temp1, less_int);

  int temp2 = 13;
  int *ptr_temp2 = &temp2;
  find(&t, ptr_temp2, less_int);

  dealloc(&t);
}
