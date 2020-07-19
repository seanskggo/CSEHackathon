#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <assert.h>

#include "ad.h"

struct ad {
    char *ad;
    char *businessName;
    int p;
    Ad next;
};

// Creates a new ad — INCOMPLETE
Ad AdNew(char *ad, char *businessName, int p) {

    Ad new = malloc(sizeof(struct ad));
    new->p = p;
    
    new->next = NULL;
    new->ad = strdup(ad);
    new->businessName = strdup(businessName);

    return new;
}

// Frees an Ad 
void FreeAd(Ad a) {
    assert(a != NULL);

    free(a->ad);
    free(a->businessName);

    free(a);

    return;
}

// prints an ad
void printAd(Ad a) {
    assert(a != NULL);

    //printf("Postcode: %d\n\n", a->p);

    fputs(a->businessName, stdout);
    printf("\n");

    printf("Ad:");
    fputs(a->ad, stdout);
    printf("\n\n");

    return;
}

int getPFromAd(Ad a) {
    return a->p;
}

Ad getNextAd(Ad a) {
    return a->next;
}

// change the next value of an Ad a to newNext
void changeNextPointer(Ad a, Ad newNext) {

   if (a->p == newNext->p) {
    a->next = newNext;
   }
   return;
}
