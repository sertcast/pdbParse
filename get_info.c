//
//  get_info.c
//  pdbParse
//
//  Created by mkaya on 26/07/2017.
//  Copyright © 2017 mkaya. All rights reserved.
//

#include "read_file.h"
#include "get_info.h"


struct atom *getAtom(struct protein *P, char chainID, int residueID, char* atomName){
    int i;
    for(i = 0; i < P->size_atom; i++){
        if(strcmp(P->atoms[i].name,atomName) == 0 && P->atoms[i].res->ID == residueID &&P->atoms[i].res->chn->ID == chainID){
            return &P->atoms[i];
        }
    }
    printf("The atom you are searching for is not in this protein. Please try again.");
    return NULL;
}
struct residue *getResidue(struct protein *P, char chainID, int residueID){
    int i;
    for(i = 0; i < P->size_residue; i++){
        if(P->atoms[i].res->ID == residueID &&P->atoms[i].res->chn->ID == chainID){
            return &P->residues[i];
        }
    }
    printf("The atom you are searching for is not in this protein. Please try again.");
    return NULL;
}
double *getCoor(struct atom *A){
    return A->coor;
};
double *getCoorOfAtom(struct protein *P, char chainID, int residueID, char* atomName){
    struct atom *A =getAtom(P, chainID, residueID, atomName);
    return A->coor;
    
}
double distanceBetweenCoor(double *firstCoor, double *secondCoor){
    double xLength = firstCoor[0] - secondCoor[0];
    double yLength = firstCoor[1] - secondCoor[1];
    double zLength = firstCoor[2] - secondCoor[2];
    return sqrt(pow(xLength,2)+pow(yLength,2)+pow(zLength,2));
}

double distanceBtwAtom (struct atom *A, struct atom *B) {
    return distanceBetweenCoor(A->coor, B->coor);
}

double distanceBtwResidue(struct residue *A, struct residue *B){
    double shortestDistance = 0.0;
    int size_atomA = A->size_atom;
    int size_atomB = B->size_atom;
    struct atom *atomA, *atomB;
    atomA = A->atoms;
    atomB = B->atoms;
    int i, j;
    
    for (i=0; i<size_atomA; i++ ) {
        for (j=0; j<size_atomB; j++ ) {
            if(shortestDistance != 0.0 && distanceBtwAtom(atomA, atomB) < shortestDistance){
                shortestDistance = distanceBtwAtom(atomA, atomB);
            }else if(shortestDistance == 0){
                shortestDistance = distanceBtwAtom(atomA, atomB);
            }
            atomB++;
        }
        atomA++;
        atomB = B->atoms;
    }
    return shortestDistance;
}


