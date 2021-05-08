#ifndef NODE_H
#define NODE_H

typedef struct Node Node;
struct Node
{
  void *value;
  Node *left;
  Node *right;
  Node *parent;
  int height;
};

#endif
