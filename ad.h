// Interface for the AD ADT

#ifndef AD_H
#define AD_H

typedef struct ad *Ad;


// Creates a new ad
Ad AdNew(char *ad, char *businessName, int postcode);

// Frees an Ad
Ad AdFree(Ad a);

// prints an ad
void printAd(Ad a);

// get the int postcode value from an Ad
int getPFromAd(Ad a);

// returns the next Ad in the list
Ad getNextAd(Ad a);

// Changes the next pointer of an Ad
// Generally used for appending something to the end of the list
void changeNextPointer(Ad a, Ad newNext);


#endif
