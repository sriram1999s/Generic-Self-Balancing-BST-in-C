#include <stdio.h>
#include <stdbool.h>

#include "bst.h"
#include "bst_iterator.h"

bool has_prev(const bst_iterator it)
{
  if (!it.current) return false;

  Node *curr = it.current;
  if (curr->left) return true;

  if (curr->parent && curr == curr->parent->right) {
    return true;
  }

  if (curr->parent && curr == curr->parent->left) {
    while (curr->parent->value && curr->parent->left == curr) curr = curr->parent;
    curr = curr->parent;
    if (curr->value) return true;
    else return false;
  }

  return false;

}

bool has_next(const bst_iterator it)
{
  if (!it.current) return false;

  Node *curr = it.current;

  if (curr->right) return true;

  if (curr->parent && curr == curr->parent->left) {
    return true;
  }

  if (curr->parent && curr == curr->parent->right) {
    while (curr->parent->value && curr->parent->right == curr) curr = curr->parent;
    curr = curr->parent;
    if (curr->value) return true;
    else return false;
  }

  return false;
}

bool equals(const bst_iterator it1, const bst_iterator it2)
{
  return (it1.current == it2.current);
}

static void init_iterator(bst_iterator *it, Node *ptr)
{
  it->current = ptr;
}

bst_iterator begin(const Bst *tree)
{
  bst_iterator it;
  init_iterator(&it, NULL);

  if (!tree->root_) return it;

  Node *ptr = tree->root_;

  while (ptr->left) {
    ptr = ptr->left;
  }

  init_iterator(&it, ptr);

  return it;
}

bst_iterator end(const Bst *tree)
{
  bst_iterator it;
  Node *temp = tree->end_;
  init_iterator(&it, temp);

  return it;
}

void* dereference(const bst_iterator it)
{
  return it.current->value;
}

bst_iterator get_prev(const bst_iterator it)
{
  bst_iterator prev_it;
  init_iterator(&prev_it, NULL);

  if(!it.current) return prev_it;
  Node *curr = it.current;

  if(curr->left)
  {
    curr = curr->left;
    while(curr->right)
    {
      curr = curr->right;
    }
    init_iterator(&prev_it, curr);
    return prev_it;
  }
  if (curr->parent && curr == curr->parent->right) {
    curr = curr->parent;
    init_iterator(&prev_it, curr);
    return prev_it;
  }
  if (curr->parent && curr == curr->parent->left) {
    while (curr->parent->value && curr->parent->left == curr) curr = curr->parent;
    curr = curr->parent;
    init_iterator(&prev_it, curr);
    return prev_it;
  }
  return prev_it;
}

bst_iterator get_next(const bst_iterator it)
{
  bst_iterator next_it;
  init_iterator(&next_it, NULL);

  if(!it.current) return next_it;

  Node *curr = it.current;

  if (curr->right) {
    curr = curr->right;
    while (curr->left) curr = curr->left;
	init_iterator(&next_it, curr);
	return next_it;
  }

  if (curr->parent && curr == curr->parent->left) {
    curr = curr->parent;
    init_iterator(&next_it, curr);
    return next_it;
  }

  if (curr->parent && curr == curr->parent->right) {
    while (curr->parent->value && curr->parent->right == curr) curr = curr->parent;
    curr = curr->parent;
    init_iterator(&next_it, curr);
    return next_it;

  }

  return next_it;
}

bst_iterator find(const Bst *tree, void *val, bool( *less_than)(const void *, const void *)) // to be modded
{
  bst_iterator it;
  init_iterator(&it, NULL);
  if (!tree || !tree->end_) return it;
  Node *trav = tree->root_;
  while (trav) {
    if (!less_than(trav->value, val) && !less_than(val, trav->value)) {
      init_iterator(&it, trav);
      return it;
    }
    if (less_than(trav->value, val)) {
      trav = trav->right;
    } else {
      trav = trav->left;
    }

  }
  init_iterator(&it, tree->end_);
  return it;
}
