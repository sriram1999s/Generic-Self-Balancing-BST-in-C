#ifndef BST_ITERATOR_H
#define BST_ITERATOR_H

#include "bst.h"

typedef struct bst_iterator bst_iterator;
struct bst_iterator
{
  Node *current;
};

bool has_next(const bst_iterator);
bool has_prev(const bst_iterator);
bool equals(const bst_iterator, const bst_iterator);
bst_iterator begin(const Bst *);
bst_iterator end(const Bst *);
void* dereference(const bst_iterator);
bst_iterator get_next(const bst_iterator);
bst_iterator get_prev(const bst_iterator);
bst_iterator find(const Bst *tree, void *val, bool (*less_than)(const void *, const void *));

#endif
