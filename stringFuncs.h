//
//  stringFuncs.h
//  pdbParse
//
//  Created by mkaya on 26/07/2017.
//  Copyright © 2017 mkaya. All rights reserved.
//

#ifndef stringFuncs_h
#define stringFuncs_h
#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <string.h>
#include <ctype.h>
#include <stdbool.h>

char *getString(char *string,int baslangic, int bitis);
double getDouble(char *string,int baslangıc, int bitis);
int getInt(char *string,int baslangıc, int bitis);
char getChar(char *string,int sira);
#endif /* stringFuncs_h */
