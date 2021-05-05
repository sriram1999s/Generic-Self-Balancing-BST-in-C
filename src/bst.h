#ifndef BST_H
#define BST_H
typedef struct Node Node;
struct Node
{
  void *value;
  Node *left;
  Node *right;
};

typedef struct Bst Bst;
struct Bst
{
  Node *root_;
  int size_;
};

void init_bst(Bst *tree);
void insert_bst(Bst *tree, void *val);
void _dealloc(Node *n);
void dealloc(Bst *tree);

void _inorder(const Node *n, void (*print)(const void *));
void inorder(const Bst *tree, void (*print)(const void *));
#endif
