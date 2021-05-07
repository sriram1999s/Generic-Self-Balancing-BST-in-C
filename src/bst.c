#include<stdio.h>
#include<stdlib.h>
#include<assert.h>
#include "bst.h"

void init_bst(Bst *tree)
{
  if (!tree) return;
  tree->end_ = (Node*)malloc(sizeof(Node));
  tree->end_->value = NULL;
  tree->end_->left = NULL;
  tree->end_->right = NULL;


  tree->root_ = NULL;
  tree->size_ = 0;
}

void bst_insert(Bst *tree, void *val, bool( *less_than)(const void *, const void *))
{
  assert(val != NULL);
  if (!tree || !tree->end_) return;
  if (!tree->root_) {
    tree->root_ = (Node*) malloc(sizeof(Node));
    tree->root_->value = val;
    tree->root_->left = tree->root_->right = NULL;

    tree->root_->parent = tree->end_;
    tree->end_->left = tree->root_;
    tree->size_ = 1;
    return;
  }

  Node *trav = tree->root_;
  Node *prev = NULL;

  while (trav) {
    prev = trav;
    if (!less_than(prev->value, val) && !less_than(val, prev->value)) break;
    if (less_than(trav->value, val)) {
      trav = trav->right;
    } else {
      trav = trav->left;
    }
  }

  if (!less_than(prev->value, val) && !less_than(val, prev->value)) return;

  Node *temp = (Node*) malloc(sizeof(Node));
  temp->value = val;
  temp->left = NULL;
  temp->right = NULL;
  temp->parent = NULL;

  if (less_than(prev->value, val)) {
    prev->right = temp;
  } else {
    prev->left = temp;
  }

  temp->parent = prev;
  ++(tree->size_);
}

void _dealloc(Node *n)
{
  if (n) {
    _dealloc(n->left);
    _dealloc(n->right);
    free(n);
  }
}

void dealloc(Bst *tree)
{
  if (tree)
    _dealloc(tree->end_);
}

int get_size(const Bst *tree)
{
    if(!tree || !tree->end_)
    return 0;

    return tree->size_;
}

void _inorder(const Node *n, void( *print)(const void *))
{
  if (n) {
    _inorder(n->left, print);
    print(n->value);
    _inorder(n->right, print);
  }
}

void inorder(const Bst *tree, void( *print)(const void *))
{
  if (tree) {
    Node *trav = tree->root_;
    _inorder(trav, print);
    printf("\n");
  }
}

void bst_remove(Bst *tree, void *val, bool( *less_than)(const void *, const void *))
{
  if (!tree || !tree->end_ || !tree->root_) return;

  Node *trav = tree->root_;
  Node *prev = tree->end_;

  while (trav && (less_than(trav->value, val) || less_than(val, trav->value))) {
    prev = trav;
    if (less_than(trav->value, val)) {
      trav = trav->right;
    } else {
      trav = trav->left;
    }
  }

  if (trav) {
    --(tree->size_);
    if (prev->right == trav) {
      if (!trav->right || !trav->left) // trav is a leaf or trav has one child
      {
        if (trav->right) {
          prev->right = trav->right;
        trav->right->parent = prev;
        } else {
          prev->right = trav->left;
        if (trav->left) trav->left->parent = prev;
        }
        free(trav);
      } else {
        Node *inorder_prev = NULL;
        Node *inorder_succ = trav->right;
        while (inorder_succ->left) {
          inorder_prev = inorder_succ;
          inorder_succ = inorder_succ->left;
        }
        trav->value = inorder_succ->value;
        if (inorder_prev) {
          inorder_prev->left = inorder_succ->right;
          if (inorder_succ->right) inorder_succ->right->parent = inorder_prev;
        } else {
          trav->right = inorder_succ->right;
          if (inorder_succ->right) inorder_succ->right->parent = trav;
        }
        free(inorder_succ);
      }
    }
    else // deleting root has to come here
    {
      if (!trav->right || !trav->left)
      {
        if (trav->right)
        {
          prev->left = trav->right;
		      trav->right->parent = prev;
        } else
        {
          prev->left = trav->left;
		      if (trav->left) trav->left->parent = prev;
        }
        if(trav == tree->root_) // in case of deleting root
        {
          tree->root_ = tree->end_->left;
        }
        free(trav);
      }
      else
      {
        Node *inorder_prev = NULL;
        Node *inorder_succ = trav->right;
        while (inorder_succ->left) {
          inorder_prev = inorder_succ;
          inorder_succ = inorder_succ->left;
        }
        trav->value = inorder_succ->value;
        if (inorder_prev) {
          inorder_prev->left = inorder_succ->right;
          if (inorder_succ->right) inorder_succ->right->parent = inorder_prev;
        } else {
          trav->right = inorder_succ->right;
          if (inorder_succ->right) inorder_succ->right->parent = trav;
        }
        free(inorder_succ);
      }
    }
  }
}
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
