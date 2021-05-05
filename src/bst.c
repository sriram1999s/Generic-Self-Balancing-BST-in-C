#include<stdio.h>
#include<stdlib.h>

#include "bst.h"
void init_bst(Bst *tree)
{
  if(!tree) return;
  tree->root_ = NULL;
  tree->size_ = 0;
}

void insert_bst(Bst *tree, void *val)
{
  if(!tree) return;
  if(!tree->root_)
  {
    tree->root_ = (Node*)malloc(sizeof(Node));
    tree->root_->value = val;
    tree->root_->left = tree->root_->right = NULL;
  }
}

void _dealloc(Node *n)
{
  if(n)
  {
    _dealloc(n->left);
    _dealloc(n->right);
    free(n);
  }
}
void dealloc(Bst *tree)
{
  if(tree)
  _dealloc(tree->root_);
}

void _inorder(const Node *n, void (*print)(const void *))
{
  if(n)
  {
    _inorder(n->left, print);
    print(n->value);
    _inorder(n->right, print);
  }
}

void inorder(const Bst *tree, void (*print)(const void *))
{
  if(tree)
  {
    Node *trav = tree->root_;
    _inorder(trav, print);
    printf("\n");
  }
}
