# Generic Self-Balancing Binary Search Tree in C

Code can be found [here](https://github.com/sriram1999s/DesignPatterns/tree/main/src)

Examples can be found [here](https://github.com/sriram1999s/DesignPatterns/tree/main/src/test_files)

An example using a user defined type, complete with predicate and print functions can be found [here](https://github.com/sriram1999s/DesignPatterns/blob/main/src/test_files/5_testing.c)

## Functionalities

- [Insertion](#Insertion)
- [Removal](#Removal)
- [Finding](#Finding)
- [Copying](#Copying)
- [Union](#Union)
- [Deallocation](#Deallocation)

- <font size="5"> [Iterators](#Iterators) </font>
	- Bidirectional (Move in the inorder fashion)
	- Interfaces Supported:
		- [begin](#Begin)
		- [end](#End)
		- [has_next](#Check-and-go-forward)
		- [get_next](#Check-and-go-forward)
		- [has_prev](#Check-and-go-backward)
		- [get_prev](#Check-and-go-backward)
		- [equals](#Iterator-Equality)
		- [dereference](#Iterator-Dereferencing)

# Usage of BST

## Inclusion

```c
#include "bst.h"
```

## Declaration and Initialization

```c
Bst t;
init_bst(&t);
```

## Insertion

For insertion, a predicate function must be provided. Here is an example of a predicate function for the type ```int```

```c
bool less_int(const void * x, const void *y)
{
  return *(int*)x < *(int*)y;
}
```

```c
// assuming type int
int a = 10;
bst_insert(&t, &a, less_int);
```
Here, ```t``` is of type ```Bst```, ```a``` can be of any type, ```less_int``` is the predicate function that determines the inherent association between data in the tree.
<br><br>
To insert an array of elements:

Syntax: ```bst_array_insert(<tree>, <array>, <length_of_array>, <predicate>);```

```c
int len = 6;
int elts[] = {1, 2, 0, 8, -7, 15};

bst_array_insert(&tree, elts, len, less_int);
```

## Removal

For removal, a predicate function must be provided.

```c
int a = 10;
bst_remove(&t, &a, less_int);
```
Here, ```t``` is of type ```Bst```, ```a``` can be of any type, ```less_int``` is the predicate function that determines the inherent association between data in the tree.

## Finding

For finding, a predicate function must be provided.

```c
#include "bst_iterator.h"

int a = 10;
bst_iterator it = bst_find(&t, &a, less_int);
```
Here, ```it``` is of type ```bst_iterator```, ```t``` is of type ```Bst```, ```a``` can be of any type, ```less_int``` is the predicate function that determines the inherent association between data in the tree.

## Copying

```c
// assume tree is of type Bst

Bst tree_copy;
init_bst(&tree_copy);

bst_copy(&tree_copy, &tree);
```

## Union

Syntax: ```bst_union(<destination>, <tree1>, <tree2>, <predicate>);```

```c
Bst unified;
init_bst(&unified);

bst_union(&unified, &tree_1, &tree_2, less_double);
```
Here, ```tree_1``` and ```tree_2``` are of type ```Bst```, ```less_int``` is the predicate function that determines the inherent association between data in the tree.

## Traversal

A function must be provided for printing the generic data contained in the tree. An example of such a function for the type ```int``` is as follows:

```c
void print_int(const void *ptr)
{
  printf("%d\t", *(int*)ptr);
}
```

The supported methods of traversal are:

```c
inorder(&t, print_int);
preorder(&t, print_int);
postorder(&t, print_int);
```

## Deallocation

> This is a very important step to stop to avoid memory leaks

```c
deallocate_bst(&t);
```

# Usage of BST Iterators

## Inclusion

```c
#include "bst_iterator.h"
```

## Begin

```c
bst_iterator it = begin(&t);
```

## End

```c
bst_iterator it = end(&t);
```

## Forward Iteration

### Check and go forward

```c
bst_iterator it = begin(&t);
if (has_next(it)) {
	it = get_next(it);
}
```

### Check and go backward

```c
bst_iterator it = end(&t);
if (has_prev(it)) {
	it = get_prev(it);
}
```

## Iterator Equality

```c
bst_iterator it1 = begin(&t);
bst_iterator it2 = begin(&t);

if (equals(it1, it2)) {
	printf("Equal\n");
}
```

## Iterator Dereferencing

Dereferencing the iterator returns the generic data. Typecasting is required. One way to print the dereferenced value is as follows:

```c
void print_int(const void *ptr)
{
  printf("%d\t", *(int*)ptr);
}
```
```c
bst_iterator it = begin(&t);

if (dereference(it)) {
	print_int(dereference(it));
}
```
