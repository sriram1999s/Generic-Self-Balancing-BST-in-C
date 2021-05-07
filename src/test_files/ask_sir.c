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

  bst_insert(&t, ptr1, less_int);
  bst_insert(&t, ptr2, less_int);
  bst_insert(&t, ptr3, less_int);
  bst_insert(&t, ptr4, less_int);
  bst_insert(&t, ptr5, less_int);
  bst_insert(&t, get_ptr(int, 1, 10), less_int);
  bst_insert(&t, get_ptr(int, 2, 5), less_int);
  bst_insert(&t, get_ptr(int, 3, 2), less_int);
  bst_insert(&t, get_ptr(int, 4, 9), less_int);
  bst_insert(&t, get_ptr(int, 5, 6), less_int);

  inorder(&t, print_int);

  int temp1 = 5;
  int *ptr_temp1 = &temp1;
  find(&t, ptr_temp1, less_int);

  int temp2 = 13;
  int *ptr_temp2 = &temp2;
  find(&t, ptr_temp2, less_int);

  dealloc(&t);
}
