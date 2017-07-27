//
//  get_info.h
//  pdbParse
//
//  Created by mkaya on 26/07/2017.
//  Copyright © 2017 mkaya. All rights reserved.
//

#ifndef get_info_h
#define get_info_h

#include <stdio.h>
struct atom *getAtom(struct protein *P, char chainID, int residueID, char* atomName);
struct residue *getResidue(struct protein *P, char chainID, int residueID);
double *getCoor(struct atom *A);
double *getCoorOfAtom(struct protein *P, char chainID, int residueID, char* atomName);
double distanceBetweenCoor(double *firstCoor, double *secondCoor);
double distanceBtwAtom (struct atom *A, struct atom *B);
double distanceBtwResidue(struct residue *A, struct residue *B);
void contacts(struct protein *P, double maxDist, int criteria);
#endif /* get_info_h */
