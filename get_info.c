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
double distanceBetweenCA(struct residue *A,struct residue *B){
    int size_atomA = A->size_atom;
    int size_atomB = B->size_atom;
    struct atom *atomA, *atomB;
    atomA = A->atoms;
    atomB = B->atoms;
    int i, j;
    for (i=0; i<size_atomA; i++ ){
        for (j=0; j<size_atomB; j++ ){
            if(strcmp(atomA->name," CA ")==0 && strcmp(atomB->name," CA ")==0){
                return distanceBtwAtom(atomA, atomB);
            }
            atomB++;
        }
        atomA++;
        atomB = B->atoms;
    }
    //printf("There is no CA\n");
    return 0.0;
}
void contacts(struct protein *P, double maxDist, int criteria){
    int a,b,x = 0;
    for(a = 0; a < P->size_residue-criteria; a++){
        for(b = a + criteria; b < P->size_residue; b++){
            if(distanceBtwResidue(&P->residues[a], &P->residues[b])<=maxDist){
            printf("%d(%c)\t\t%d(%c)\t\t%.5lf\t\t%.5lf\n",P->residues[a].ID,P->residues[a].chn->ID,P->residues[b].ID,P->residues[b].chn->ID,distanceBtwResidue(&P->residues[a] , &P->residues[b]),distanceBetweenCA(&P->residues[a], &P->residues[b]));
                x++;
            }
        }
    }
    printf("There is %d residue who interacts\n",x);
}

void contactsChain(struct chain *C, double maxDist, int criteria){
    int a,b,x = 0;
    struct residue *resA, *resB;
    for(a = 0; a < C->size_residue-criteria; a++){
        resA = C->residues + a;
        for(b = a + criteria; b < C->size_residue; b++){
            resB = C->residues + b;
            if(distanceBtwResidue(resA, resB)<=maxDist){
                printf("%d(%c)\t\t%d(%c)\t\t%.5lf\t\t%.5lf\n",resA->ID,resA->chn->ID,resB->ID,resB->chn->ID,distanceBtwResidue(resA , resB),distanceBetweenCA(resA, resB));
                x++;
            }
        }
    }
    printf("There is %d residue who interacts\n",x);
}



