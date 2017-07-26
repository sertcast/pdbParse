//
//  main.c
//  pdbParse
//
//  Created by mkaya on 26/07/2017.
//  Copyright © 2017 mkaya. All rights reserved.
//

#include <stdio.h>
#include "read_file.h"
#include "get_info.h"



int main() {
    struct protein *P = NULL;
    P = readFile("/Users/mkaya/Desktop/PDB_read/PDB_read/2CI2.pdb");
    P = freeProtein(P);
    return 0;
}
