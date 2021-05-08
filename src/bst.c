#include <stdio.h>
#include <stdlib.h>
#include <assert.h>

#include "bst.h"

static Node *create_node(void *val, Node *parent)
{
  Node *new = (Node*)malloc(sizeof(Node));
  new->value = val;
  new->left = NULL;
  new->right = NULL;
  new->height = 1;
  new->parent = parent;
  return new;
}

static int height(const Node *node)
{
  if(!node) return 0;
  return node->height;
}

static int balance(const Node *node)
{
  if(!node)
    return 0;
  return height(node->left) - height(node->right);
}

inline static int max(int a , int b)
{
  return (a > b) ? a : b;
}

Node *right_rotate(Node *y)
{
  Node *left_y = y->left;
  Node *r_left_y = left_y->right;

  left_y->right = y;
  left_y->parent = y->parent;
  y->parent = left_y;

  y->left = r_left_y;
  if(r_left_y) r_left_y->parent = y;

  left_y->height = 1 + max(height(left_y->left), height(left_y->right));
  y->height = 1 + max(height(y->left), height(y->right));

  return left_y;
}

Node *left_rotate(Node *y)
{
  Node *right_y = y->right;
  Node *l_right_y = right_y->left;

  right_y->left = y;
  right_y->parent = y->parent;
  y->parent = right_y;

  y->right = l_right_y;
  if(l_right_y) l_right_y->parent = y;

  right_y->height = 1 + max(height(right_y->left), height(right_y->right));
  y->height = 1 + max(height(y->left), height(y->right));

  return right_y;
}

void init_bst(Bst *tree)
{
  if (!tree) return;
  tree->end_ = create_node(NULL, NULL);


  tree->root_ = NULL;
  tree->size_ = 0;
}

static void update_height(Node *n)
{
  if(!n) return;
  n->height = max(height(n->left), height(n->right));
  update_height(n->left);
  update_height(n->right);

}

static Node * _insert(Node *node, void *val, Node *parent, bool( *less_than)(const void *, const void *))
{
  if(!node) return create_node(val, parent);

  if(!less_than(node->value, val) && !less_than(val, node->value)) return node;

  if(less_than(node->value, val)) node->right = _insert(node->right, val, node, less_than);
  else node->left = _insert(node->left, val, node, less_than);

  node->height = 1 + max(height(node->left), height(node->right));

  int bal = balance(node);

  if(bal > 1)
  {
    if(less_than(val, node->left->value)) return right_rotate(node);
    else
    {
      node->left =  left_rotate(node->left);
      return right_rotate(node);
    }
  }

  if(bal < -1)
  {
    if(less_than(node->right->value, val)) return left_rotate(node);
    else
    {
      node->right = right_rotate(node->right);
      return left_rotate(node);
    }
  }
  return node;
}

void bst_insert(Bst *tree, void *val, bool( *less_than)(const void *, const void *))
{
  assert(val != NULL);
  if(!tree) return;
  tree->root_ = _insert(tree->root_, val, tree->end_, less_than);
  tree->end_->left = tree->root_;
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

void deallocate_bst(Bst *tree)
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

void _preorder(const Node *n, void (*print)(const void *n))
{
  if (n) {
    print(n->value);
    _preorder(n->left, print);
    _preorder(n->right, print);
  }
}

void preorder(const Bst *tree, void (*print)(const void *))
{
  if (tree) {
    Node *trav = tree->root_;
    _preorder(trav, print);
    printf("\n");
  }
}

static Node *_remove(Node *node, void *val, Node *par, bool( *less_than)(const void *, const void *))
{
  if(!node) return node;

  if(!less_than(val, node->value) && !less_than(node->value, val))
  {
    if(!node->left || !node->right)
    {
      Node *temp = node->left ? node->left :node->right;
      if (temp == NULL)
      {
        temp = node;
        node = NULL;
      }
      else *node = *temp;
      free(temp);
    }
    else
    {
      Node *inorder_prev = NULL;
      Node *inorder_succ = node->right;
      while (inorder_succ->left) {
        inorder_prev = inorder_succ;
        inorder_succ = inorder_succ->left;
      }
      node->value = inorder_succ->value;
      node->right = _remove(node->right, inorder_succ->value, node, less_than);
    }

  }
  else if(less_than(val, node->value)) node->left = _remove(node->left, val, node, less_than);
  else node->right = _remove(node->right, val , node, less_than);

  if(!node) return node;
  node->height = 1 + max(height(node->left), height(node->right));

  int bal = balance(node);

  if(bal > 1)
  {
    if(less_than(val, node->left->value)) return right_rotate(node);
    else
    {
      node->left =  left_rotate(node->left);
      return right_rotate(node);
    }
  }

  if(bal < -1)
  {
    if(less_than(node->right->value, val)) return left_rotate(node);
    else
    {
      node->right = right_rotate(node->right);
      return left_rotate(node);
    }
  }
  return node;
}

void bst_remove(Bst *tree, void *val, bool( *less_than)(const void *, const void *))
{
  if(!tree || !tree->root_) return;
  tree->root_ = _remove(tree->root_, val, tree->end_, less_than);
  tree->end_->left = tree->root_;
  --(tree->size_);
}
