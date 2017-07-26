//
//  take_info.c
//  pdbParse
//
//  Created by mkaya on 26/07/2017.
//  Copyright © 2017 mkaya. All rights reserved.
//

#include "take_info.h"
#include "take_info.h"
#include "stringFuncs.h"
int takeNumOfAtom(char *fileName){
    char line[82];
    int counter = 0;
    FILE *file = fopen(fileName, "r");
    if (file == NULL) {
        fprintf(stderr, "Can't open input file in.list!\n");
        exit(1);
    }
    while(!feof(file)){
        fgets(line, 82, file);
        if(strncmp(line,"ATOM  ",6) == 0){
            counter++;
        }
        
    }
    fclose(file);
    return counter;
}
int takeNumOfResidue(char *fileName){
    char line[82];
    int counter = 0;
    int prevNum = 0;
    FILE *file = fopen(fileName, "r");
    if (file == NULL) {
        fprintf(stderr, "Can't open input file in.list!\n");
        exit(1);
    }
    while(!feof(file)){
        fgets(line, 81, file);
        if(strncmp(line,"ATOM  ",6) == 0 && getInt(line, 23, 26)!=prevNum){
            counter++;
            prevNum = getInt(line, 23, 26);
        }
    }
    fclose(file);
    return counter;
    
}
int takeNumOfChain(char *fileName){
    char line[82];
    int counter = 0;
    FILE *file = fopen(fileName, "r");
    if (file == NULL) {
        fprintf(stderr, "Can't open input file in.list!\n");
        exit(1);
    }
    while(!feof(file)){
        fgets(line, 81, file);
        if(strncmp(line,"TER   ",6) == 0){
            counter++;
        }
    }
    fclose(file);
    return counter;
    
}
