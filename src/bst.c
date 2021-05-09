#include <stdio.h>
#include <stdlib.h>
#include <assert.h>

#include "bst.h"
#include "bst_iterator.h"

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

static Node *right_rotate(Node *y)
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

static Node *left_rotate(Node *y)
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
}

static void update_height(Node *n)
{
  if(!n) return;
  n->height = max(height(n->left), height(n->right));
  update_height(n->left);
  update_height(n->right);

}

static Node * _insert(Node *node, void *val, Node *par, bool (*predicate)(const void *, const void *))
{
  if(!node) return create_node(val, par);

  if(!predicate(node->value, val) && !predicate(val, node->value)) return node;

  if(predicate(node->value, val)) node->right = _insert(node->right, val, node, predicate);
  else node->left = _insert(node->left, val, node, predicate);

  node->height = 1 + max(height(node->left), height(node->right));

  int bal = balance(node);

  if(bal > 1)
  {
    if(predicate(val, node->left->value)) return right_rotate(node);
    else
    {
      node->left =  left_rotate(node->left);
      return right_rotate(node);
    }
  }

  if(bal < -1)
  {
    if(predicate(node->right->value, val)) return left_rotate(node);
    else
    {
      node->right = right_rotate(node->right);
      return left_rotate(node);
    }
  }
  return node;
}

static void _copy(Node *h1, Node *h2)
{
  if (h2->left) {
    h1->left = create_node(h2->left->value, h1);
    h1->left->height = h2->left->height;
    _copy(h1->left, h2->left);
  }

  if (h2->right) {
    h1->right = create_node(h2->right->value, h1);
    h1->right->height = h2->right->height;
    _copy(h1->right, h2->right);
  }
}

void bst_copy(Bst *t1, Bst *t2)
{
  if (!t1 || !t2) return;

  deallocate_bst(t1);
  init_bst(t1);

  _copy(t1->end_, t2->end_);

  if (t1->end_->left) {
    t1->root_ = t1->end_->left;
    t1->root_->parent = t1->end_;
  }
}

void bst_insert(Bst *tree, void *val, bool (*predicate)(const void *, const void *))
{
  assert(val != NULL);
  if(!tree) return;
  tree->root_ = _insert(tree->root_, val, tree->end_, predicate);
  tree->end_->left = tree->root_;
}

void bst_union(Bst *dest, Bst *t1, Bst *t2, bool (*predicate)(const void *, const void *))
{
  // Bst dest;
  // init_bst(&dest);

  if (!t1 && !t2) return;
  printf("Here\n");

  if (!t1) {
    bst_copy(dest, t2);
    return;
  }

  if (!t2) {
    bst_copy(dest, t1);
    return;
  }

  bst_copy(dest, t1);

  bst_iterator t2_beg = begin(t2);
  bst_iterator t2_end = end(t2);
  while (!equals(t2_beg, t2_end)) {
    bst_insert(dest, t2_beg.current->value, predicate);
    t2_beg = get_next(t2_beg);
  }

  return;
}

static void _dealloc(Node *n)
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

static void _inorder(const Node *n, void( *print)(const void *))
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

static void _preorder(const Node *n, void (*print)(const void *n))
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

static void _postorder(const Node *n, void (*print)(const void *))
{
  if (n) {
    _postorder(n->left, print);
    _postorder(n->right, print);
    print(n->value);
  }
}

void postorder(const Bst *tree, void (*print)(const void *))
{
  if (tree) {
    Node *trav = tree->root_;
    _postorder(trav, print);
    printf("\n");
  }
}

static Node *_remove(Node *node, void *val, Node *par, bool( *predicate)(const void *, const void *))
{
  if(!node) return node;

  if(!predicate(val, node->value) && !predicate(node->value, val))
  {
    if(!node->left || !node->right)
    {
      Node *temp = node->left ? node->left : node->right;
      if (!temp)
      {
        free(node);
        if (par->left == node) par->left = NULL;
        else par->right = NULL;
        return NULL;
      }
      else
      {
        node->value = temp->value;
        node->left = temp->left;
        if (temp->left) temp->left->parent = node;
        node->right = temp->right;
        if (temp->right) temp->right->parent = node;
      }
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
      node->right = _remove(node->right, inorder_succ->value, node, predicate);
    }
  } else if(predicate(val, node->value)) {
    node->left = _remove(node->left, val, node, predicate);
  } else {
    node->right = _remove(node->right, val , node, predicate);
  }

  node->height = 1 + max(height(node->left), height(node->right));

  int bal = balance(node);

  if(bal > 1)
  {
    if(balance(node->left) >= 0) return right_rotate(node);
    else
    {
      node->left = left_rotate(node->left);
      return right_rotate(node);
    }
  }

  if(bal < -1)
  {
    if(balance(node->right) <= 0) return left_rotate(node);
    else
    {
      node->right = right_rotate(node->right);
      return left_rotate(node);
    }
  }
  return node;
}

void bst_remove(Bst *tree, void *val, bool( *predicate)(const void *, const void *))
{
  if(!tree || !tree->root_) return;
  tree->root_ = _remove(tree->root_, val, tree->end_, predicate);
  tree->end_->left = tree->root_;
}
