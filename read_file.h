//
//  read_file.h
//  pdbParse
//
//  Created by mkaya on 26/07/2017.
//  Copyright © 2017 mkaya. All rights reserved.
//

#ifndef readFile_h
#define readFile_h

#include "stringFuncs.h"
#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <string.h>
#include <ctype.h>
#include <stdbool.h>

struct atom {
    int ID;
    char name[5];
    double coor[3];
    struct residue *res;
};
struct residue{
    int ID;
    char name[4];
    struct atom *atoms;
    struct chain *chn;
    int size_atom;
};
struct chain{
    char ID;
    struct residue *residues;
    struct protein *prtn;
    int size_residue;
};
struct protein{
    char *name;
    struct atom *atoms;
    struct chain *chains;
    struct residue *residues;
    int size_atom;
    int size_residue;
    int size_chain;
};

int checkCommand(int x, char **y);
struct protein *readFile(char *fileName);
void freeProtein(struct protein *P);

#endif /* readFile_h */
