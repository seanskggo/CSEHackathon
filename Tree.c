// Implementation of an AVL TREE

#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <assert.h>

#include "Postcode.h"
#include "ad.h"
#include "Tree.h"

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
static Node doInsert(Node n, Ad a, int p);
static Node rotateLeft(Node n);
static Node rotateRight(Node n);
static int  height(Node n);
static int  max(int a, int b);
static Node newNode(Postcode p);
static int doTreeFind(Node n, int postcode);
void doPrintPostcodesInRange(Node n, int p, int range);
void doPrintTree(Node n);
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
        PostcodeFree(n->postcode);
        doFree(n->left);
        doFree(n->right);
        free(n);
    }
}

// Insert an ad into the tree
void TreeInsert(Tree t, Ad a, int p) {
    t->root = doInsert(t->root, a, p);
}

// internal function for TreeInsert
static Node doInsert(Node n, Ad a, int p) {
    if (n == NULL) {
        Postcode postcode = PostcodeNew(p);
        addAdToPostcode(postcode, a);
        return newNode(postcode);
    }

    // insert recursively
    int cmp = PostcodeCmp(n, a);
    if (cmp < 0) {
        n->left = doInsert(n->left, a, p);
    } else if (cmp > 0) {
        n->right = doInsert(n->right, a, p);
    } else {
        addAdToPostcode(n->postcode, a);
    }

    // insertion done
    // correct the height of the current subtree
    n->height = 1 + max(height(n->left), height(n->right));

    // rebalance the tree
    int lHeight = height(n->left);
    int rHeight = height(n->right);

    if ((lHeight - rHeight) > 1 ) {
        if (n->left != NULL && (PostcodeCmp(n->left, a) > 0)) {
            n->left = rotateLeft(n->left);
        }
        n = rotateRight(n);
    } else if ((rHeight - lHeight) > 1) {
        if (n->right != NULL && (PostcodeCmp(n->right, a) < 0)) {
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

// Returns  the height of a subtree.
// Assumes that the correct heigh is correct.
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

// check whether a postcode value is in a Tree — INCOMPLETE FUNCTION
// returns 1 if there is, 0 if there is not
int TreeFind (Tree t, int p) {
    return doTreeFind(t->root, p);
}

static int doTreeFind(Node n, int find) {
    if (n == NULL) {
        return 0;
    }

    Postcode currPostcode = getPostcodeFromNode(n);
    int currP = getPfromPostcode(currPostcode);

    if (find < currP) {
        doTreeFind(n->left, find);
    } else if (find > currP) {
        doTreeFind(n->right, find);
    } //else {
        return 1;
    //}
}

// returns the Postcode from a node
Postcode getPostcodeFromNode(Node n) {
    return n->postcode;
}

// global variable (this file only)
int affectedBusinesses = 0;

// prints postcodes in range [p - range, p + range]. Wrapper func.
int printPostcodesInRange(Tree t, int p, int range) {
   
   doPrintPostcodesInRange(t->root, p, range);
   return affectedBusinesses;
}  

void doPrintPostcodesInRange(Node n, int p, int range) {

   if (n == NULL) {
      return;
   }
   
   int nodeP = getPfromPostcode(n->postcode);
   if (nodeP <= p + 10 && nodeP >= p - 10) {
      printf("Postcode: %d\n\n", nodeP);
      
      Ad curr = getAdFromPostcode(n->postcode); 
      while (curr != NULL) {
         printAd(curr);
         affectedBusinesses++;
         curr = getNextAd(curr);
      }
   }
   
   doPrintPostcodesInRange(n->left, p, range);
   doPrintPostcodesInRange(n->right, p, range);
}

// print a dictionary wrapper function -  TEST FUNCTION
void printTree(Tree t) {
   doPrintTree(t->root);
   return;
}

// print a dictonary - internals of showDict() - TEST FUNCTION
void doPrintTree(Node n) {
   if (n == NULL) return;

   Ad curr = getAdFromPostcode(n->postcode); 
   while (curr != NULL) {
      printAd(curr);
      curr = getNextAd(curr);
   }
   
   doPrintTree(n->left);
   doPrintTree(n->right);
   
   return;
}
