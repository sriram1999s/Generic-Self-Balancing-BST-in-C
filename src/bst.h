#ifndef BST_H
#define BST_H
#include<stdbool.h>

// #define get_ptr(type, __num, value) ({ type tmp##__num = value; type *ptr##__num = &tmp##__num; ptr##__num; })

typedef struct Node Node;
struct Node
{
  void *value;
  Node *left;
  Node *right;
  Node *parent;
};

typedef struct Bst Bst;
struct Bst
{
  Node *end_;
  Node *root_;
  int size_;
};

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

void init_bst(Bst *tree);
void bst_insert(Bst *tree, void *val, bool (*less_than)(const void *, const void *));
void bst_remove(Bst *tree, void *val, bool (*less_than)(const void *, const void *));

void _dealloc(Node *n);
void dealloc(Bst *tree);

int get_size(const Bst *tree);
void _inorder(const Node *n, void (*print)(const void *));
void inorder(const Bst *tree, void (*print)(const void *));

bst_iterator find(const Bst *tree, void *val, bool (*less_than)(const void *, const void *)); //to be modified

#endif
