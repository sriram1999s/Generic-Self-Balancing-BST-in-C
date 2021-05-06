#include<stdio.h>
#include<stdlib.h>
#include "bst.h"

void init_bst(Bst *tree)
{
  if(!tree) return;
  tree->root_ = NULL;
  tree->size_ = 0;
}

void insert_bst(Bst *tree, void *val, bool (*less_than)(const void *, const void *))
{
  if(!tree) return;
  if(!tree->root_)
  {
    tree->root_ = (Node*)malloc(sizeof(Node));
    tree->root_->value = val;
    tree->root_->left = tree->root_->right = NULL;
	return;
  }

  Node *trav = tree->root_;
  Node *prev = NULL;

  while(trav)
  {
    prev = trav;
    if(!less_than(prev->value, val) && !less_than(val, prev->value)) break;
    if(less_than(trav->value, val))
    {
      trav = trav->right;
    }
    else
    {
      trav = trav->left;
    }
  }

  if(!less_than(prev->value, val) && !less_than(val, prev->value)) return;

  Node *temp = (Node*)malloc(sizeof(Node));
  temp->value = val;
  temp->left = NULL;
  temp->right = NULL;

  if(less_than(prev->value, val))
  {
    prev->right = temp;
  }
  else
  {
    prev->left = temp;
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

void find(const Bst *tree, void *val, bool (*less_than)(const void *, const void *)) // to be modded
{
  if(!tree) return;
  Node *trav = tree->root_;
  while(trav)
  {
    if(!less_than(trav->value, val) && !less_than(val, trav->value))
    {
      printf("FOUND\n");
      return;
    }
    if(less_than(trav->value, val))
    {
      trav = trav->right;
    }
    else
    {
      trav = trav->left;
    }

  }
  printf("NOT FOUND\n");
}

void remove_bst(Bst *tree, void *val, bool (*less_than)(const void *, const void *))
{
  if(!tree || !tree->root_) return;

  Node *trav = tree->root_;
  Node *prev = NULL;

  while (trav && !less_than(trav->value, val) && !less_than(val, trav->value))
  {
    prev = trav;
    if (less_than(trav->value, val))
    {
      trav = trav->right;
    }
    else
    {
      trav = trav->left;
    }
  }

  if (trav)
  {
    if (prev->right == trav)
	{
		if (!trav->right && !trav->left)
		{
			prev->right = NULL;
			free(trav);
		}
		else if (!trav->right || !trav->left)
		{
			if (trav->right)
			{
				prev->right = trav->right;
			} else if (trav->left) {
				prev->left = trav->left;
			}
			free(trav);
		}
		else
		{

		}
	}
	else
	{
		if (!trav->right && !trav->left)
		{
			prev->left = NULL;
			free(trav);
		}
		else if
		{

		}
		else
		{

		}
	}
  }
}
