#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <assert.h>

#include "Postcode.h"
#include "ad.h"
#include "Tree.h"

struct postcode {
    Ad firstAd;
    int p;
    int numAds;
};


// new postcode
Postcode PostcodeNew(int p) {

    Postcode new = malloc(sizeof(struct postcode));
    assert(new != NULL);
    new->firstAd = NULL;
    new->p = p;
    new->numAds = 0;

    return new;
}

// compare two postcodes used for inserting into the tree
// if you need another postcodeCmp function, call it something else

// Compares two postcodes. Returns a negative number if the  first   is
// bigger  than  the  second  ,  0 if they're the same, and a
// positive number if the first postcode is smaller than the second.

// takes in an Ad and an int because that's what is specified in Tree.c
// this can be changed, but you must change both files
int PostcodeCmp(Node n, Ad a) {
    assert (n != NULL && a != NULL);

    // need to get the Postcode from the Node, the
    Postcode postcode = getPostcodeFromNode(n);
    int firstP = postcode->p;
    // need to get the p from the Ad
    int secondP = getPFromAd(a);

    if (firstP > secondP) {
        return -1;
    } else if (firstP < secondP) {
        return 1;
    }

    return 0;
}

// add an Ad to Postcode
void addAdToPostcode(Postcode postcode, Ad a) {
    assert (postcode != NULL && a != NULL);

    if (postcode->firstAd == NULL) {
        postcode->firstAd = a;
        return;
    }

    // We need to loop through the list of ads to find the last
    Ad curr = postcode->firstAd;
    Ad prev = NULL;

    while (curr != NULL) {
        prev = curr;
        curr = getNextAd(curr);
    }

    // add a to the end of the list;
    changeNextPointer(prev, a);

    return;
}

// free all memory associated with a Postcode
void PostcodeFree(Postcode p) {
    assert (p != NULL);


    Ad curr = p->firstAd;
    Ad prev = NULL;
    while (curr != NULL) {
        prev = curr;
        curr = getNextAd(curr);
        free(prev);
    }

    free(p);

    return;
}

// prints all ads in a postcode 
void PostcodePrint(Postcode p) {
    assert (p != NULL);

    Ad curr = p->firstAd;
    int affectedBusinesses = 0;
    while (curr != NULL) {

        printAd(curr);
        
        affectedBusinesses++;
        curr = getNextAd(curr);
    }
    
    return;
}

// returns the int version of postcode from a Postcode
int getPfromPostcode(Postcode postcode) {
    return postcode->p;
}

// returns an Ad from the postcode
Ad getAdFromPostcode(Postcode postcode) {
   return postcode->firstAd;
}
