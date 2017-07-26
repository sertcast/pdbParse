//
//  take_info.h
//  pdbParse
//
//  Created by mkaya on 26/07/2017.
//  Copyright © 2017 mkaya. All rights reserved.
//

#ifndef take_info_h
#define take_info_h

#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <string.h>
#include <ctype.h>
#include <stdbool.h>

int takeNumOfAtom(char *fileName);
int takeNumOfResidue(char *fileName);
int takeNumOfChain(char *fileName);
#endif /* take_info_h */
