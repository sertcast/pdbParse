//
//  read_file.c
//  pdbParse
//
//  Created by mkaya on 26/07/2017.
//  Copyright © 2017 mkaya. All rights reserved.
//

#include "read_file.h"
#include "take_info.h"

void readAtomData(char *fileName, struct protein *P){
    int countAtom = 0;
    char line[82];
    char *getstring = NULL;
    FILE * file = fopen(fileName, "r");
    while (!feof(file)) {
        fgets(line, 82, file);
        if(strncmp(line , "ATOM  ", 6) == 0){
            //for atom
            P->atoms[countAtom].ID = getInt(line, 7, 11);
            getstring = getString(line, 13, 16);
            strcpy(P->atoms[countAtom].name, getstring);
            P->atoms[countAtom].coor[0] = getDouble(line, 31, 38);
            P->atoms[countAtom].coor[1] = getDouble(line, 39, 46);
            P->atoms[countAtom].coor[2] = getDouble(line, 47, 54);
            countAtom++;
        }
    }
    free(getstring);
    fclose(file);
}
void readResidueData(char *fileName, struct protein *P){
    int countAtom = 0;
    int atom_size = 0;
    int countResidue = 0;
    char line[82];
    int prevResd = 0;
    char *getstring = NULL;
    FILE * file = fopen(fileName, "r");
    while (!feof(file)) {
        fgets(line, 82, file);
        if(strncmp(line , "ATOM  ", 6) == 0){
            if(prevResd != getInt(line, 23, 26) && prevResd != 0){
                P->residues[countResidue].size_atom = atom_size;
                atom_size = 0;
                countResidue++;
                P->residues[countResidue].atoms = &P->atoms[countAtom];
                P->residues[countResidue].ID = getInt(line, 23, 26);
                getstring = getString(line, 18, 20);
                strcpy(P->residues[countResidue].name, getstring);
                prevResd = getInt(line, 23, 26);
                
            }else if(prevResd == 0){
                P->residues[countResidue].ID = getInt(line, 23, 26);
                getstring = getString(line, 18, 20);
                strcpy(P->residues[countResidue].name, getstring);
                P->residues[countResidue].atoms = &P->atoms[countAtom];
                prevResd = getInt(line, 23, 26);
            }
            P->atoms[countAtom].res = &P->residues[countResidue];
            countAtom++;
            atom_size++;
        }
    }
    free(getstring);
    P->residues[countResidue].size_atom = atom_size;
    fclose(file);
}
void readChainData(char *fileName, struct protein *P){
    int countResidue = 0;
    int residue_size = 0;
    int countChain = 0;
    char line[82];
    int prevResd = 0;
    char prevChn = 'a';
    FILE * file = fopen(fileName, "r");
    while (!feof(file)) {
        fgets(line, 82, file);
        if(strncmp(line , "ATOM  ", 6) == 0){
            if(prevResd != getInt(line, 23, 26)){
                if(prevChn != getChar(line, 22)&&prevChn != 'a'){
                    P->chains[countChain].size_residue = residue_size;
                    residue_size = 0;
                    countChain++;
                    P->chains[countChain].ID = getChar(line, 22);
                    P->chains[countChain].residues = &P->residues[countResidue];
                    prevChn = getChar(line, 22);
                }else if(prevChn == 'a'){
                    P->chains[countChain].ID = getChar(line, 22);
                    P->chains[countChain].residues = &P->residues[countResidue];
                    prevChn = getChar(line, 22);
                }
                P->residues[countResidue].chn = &P->chains[countChain];
                residue_size++;
                countResidue++;
            }
        }
    }
    P->chains[countChain].size_residue = residue_size;
    fclose(file);
}
void readProteinData(char *fileName, struct protein *P){
    char line[82];
    int countChain = 0;
    char prevChn = 'a';
    FILE * file = fopen(fileName, "r");
    while (!feof(file)) {
        fgets(line, 82, file);
        if(strncmp(line , "ATOM  ", 6) == 0){
            if(prevChn != getChar(line, 22)){
                P->chains[countChain].prtn = P;
                countChain++;
                prevChn = getChar(line, 22);
            }
        }
    }
    P->size_atom = takeNumOfAtom(fileName);
    P->size_residue = takeNumOfResidue(fileName);
    P->size_chain= takeNumOfChain(fileName);
    P->name = fileName;
    fclose(file);
}
struct protein *readFile(char *fileName){
    struct protein *P;
    int numOfAtoms =takeNumOfAtom(fileName);
    int numOfResidues =takeNumOfResidue(fileName);
    int numOfChains =takeNumOfChain(fileName);
    
    P = (struct protein*)malloc(1*sizeof(struct protein));
    P->atoms = (struct atom*)malloc(numOfAtoms*sizeof(struct atom));
    P->residues = (struct residue*)malloc(numOfResidues*sizeof(struct residue));
    P->chains = (struct chain*)malloc(numOfChains*sizeof(struct chain));
    
    readAtomData(fileName, P);
    readResidueData(fileName, P);
    readChainData(fileName, P);
    readProteinData(fileName, P);
    
    return P;
};
void freeProtein(struct protein *P){
    free(P->atoms);
    free(P->residues);
    free(P->chains);
    free(P);
}



