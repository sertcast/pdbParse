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
double distanceBtwAtom (struct atom *A, struct atom *B);
double distanceBtwResidue(struct residue *A, struct residue *B);
#endif /* get_info_h */
