// Inerface to the AVL tree ADT
#ifndef TREE_H
#define TREE_H

#include "Postcode.h"

typedef struct tree *Tree;
typedef struct node *Node;
typedef struct postcode *Postcode;

// Creates a new empty tree
Tree TreeNew(void);

// Frees the tree
void TreeFree(Tree t);

// Insert an Ad into the tree
void TreeInsert(Tree t, Ad a, int p);

// special function that returns the Postcode in the node
Postcode getPostcodeFromNode(Node n);

// check whether a postcode value is in a Tree 
int TreeFind (Tree t, int postcode);

// prints postcodes in range [p - range, p + range] returns number of 
// ads in the range
int printPostcodesInRange(Tree t, int p, int range);

// print a dictionary wrapper function -  TEST FUNCTION
void printTree(Tree t);

#endif
