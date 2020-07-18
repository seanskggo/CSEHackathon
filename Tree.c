// Implementation of an AVL TREE

#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>

#include "Postcode.h"
#include "ad.h"
#include "Tree.h"

typedef struct node *Node;

struct node {
    Postcode postcode;
    int  height;
    Node left;
    Node right;
};

struct tree {
    Node root;
};

//////////////////////
// Function Prototypes
static void doFree(Node n);
static Node doInsert(Node n, Ad ad);
static Node rotateLeft(Node n);
static Node rotateRight(Node n);
static int  height(Node n);
static int  max(int a, int b);
static Node newNode(Postcode p);
///////////////////////

// Creates a new empty tree
Tree TreeNew(void) {
   Tree t = malloc(sizeof(*t));
   assert(t != NULL);
   t->root = NULL;
   return t;
}

// Frees the tree
void TreeFree(Tree t) {
   doFree(t->root);
   free(t);
}

// internal function for free
static void doFree(Node n) {
    if (n != NULL) {
        PostcodeFree(n->postocde);
        doFree(n->left);
        doFree(n->right);
        free(n);
    }
}

// Insert an ad into the tree
void TreeInsert(Tree t, Ad a, int postcode) {
    t->root = doInsert(t->root, ad);
}

// should be complete, but worth double checking with 2521 slides
static Node doInsert(Node n, Ad a, int p) {
    if (n == NULL) {
        return newNode(ad);
    }

    // insert recursively
    int cmp = postcodeCmp(a, p);
    if (cmp < 0) {
        n->left = doInsert(n->left, a, p);
    } else if (cmp > 0) {
        n->right = doInsert(n->right, a, p);
    } else {
        addAdToPostcode();
        return n;
    }

    // insertion done
    // correct the height of the current subtree
    n->height = 1 + max(height(n->left), height(n->right));

    // rebalance the tree
    int lHeight = height(n->left);
    int rHeight = height(n->right);

    if ((lHeight - rHeight) > 1 ) {
        if (n->left != NULL && (PostcodeCmp(a, p) > 0)) {
            n->left = rotateLeft(n->left);
        }
        n = rotateRight(n);
    } else if ((rHeight - lHeight) > 1) {
        if (n->right != NULL && (PostcodeCmp(a, p) < 0)) {
            n->right = rotateRight(n->right);
        }
        n = rotateLeft(n);
    }

    return n;
}

// creates an newturns a newNode
static Node newNode(Postcode p) {
    Node n = malloc(sizeof(*n));
    assert(n != NULL);

    n->postcode = p;
    n->height = 0;
    n->left = NULL;
    n->right = NULL;
    return n;
}

// Rotates  the  given  subtree left and returns the root of the updated
// subtree.
static Node rotateLeft(Node n) {
    if (n == NULL || n->right == NULL) {
        return n;
    } else {
        Node n2 = n->right;
        n->right = n2->left;
        n2->left = n;
        return n2;
    }
}

// Rotates the given subtree right and returns the root of  the  updated
// subtree.
static Node rotateRight(Node n) {
    if (n == NULL || n->left == NULL) {
        return n;
    } else {
        Node n2 = n->left;
        n->left = n2->right;
        n2->right = n;
        return n2;
    }
}

// Returns  the height of a subtree while assuming that the height field
// of the root node of the subtree is correct
static int height(Node n) {
    if (n == NULL) {
        return -1;
    } else {
        return n->height;
    }
}

static int max(int a, int b) {
    return a > b ? a : b;
}

// Ad-ADT specific Tree functions:

// check whether a postcode value is in a Tree — INCOMPLETE FUNCTION
int TreeFind (BSTree t, int postcode)
{
	//
}
