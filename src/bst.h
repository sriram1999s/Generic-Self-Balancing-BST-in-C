#ifndef BST_H
#define BST_H

#include <stdbool.h>

#include "node.h"

// #define get_ptr(type, __num, value) ({ type tmp##__num = value; type *ptr##__num = &tmp##__num; ptr##__num; })

typedef struct Bst Bst;
struct Bst
{
  Node *end_;
  Node *root_;
  int size_;
};

void init_bst(Bst *tree);
void bst_insert(Bst *tree, void *val, bool (*predicate)(const void *, const void *));

#define bst_array_insert(tree, arr, length, predicate) { for (int i=0; i<length; ++i) {bst_insert(tree, &arr[i], predicate);} }

void bst_copy(Bst *, Bst *);
void bst_union(Bst *, Bst *, Bst *, bool (*predicate)(const void *, const void *));
void bst_remove(Bst *tree, void *val, bool (*predicate)(const void *, const void *));
void inorder(const Bst *tree, void (*print)(const void *));
void preorder(const Bst *tree, void (*print)(const void *));
void postorder(const Bst *tree, void (*print)(const void *));
void deallocate_bst(Bst *tree);

#endif
