// Interface for the Postcode ADT
#ifndef POSTCODE_H
#define POSTCODE_H

#include "ad.h"
#include "Tree.h"

typedef struct postcode *Postcode;
typedef struct node *Node;

// new postcode
Postcode PostcodeNew(int p);

// compare two postcodes given in a specific form
int PostcodeCmp(Node n, Ad a);

// add an Ad to our postocde
void addAdToPostcode(Postcode p, Ad a);

// free all memory associated with a Postcode
void PostcodeFree(Postcode p);

// print all Ads in a ostcode
void PostcodePrint(Postcode p);

// add an Ad to a Postcode
void addAdToPostcode(Postcode p, Ad a);

// get the int version of a postcode from a Postcode
int getPfromPostcode(Postcode postcode);

// get an Ad from a Postcode
Ad getAdFromPostcode(Postcode postcode);

#endif
