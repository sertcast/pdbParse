//
//  stringFuncs.c
//  pdbParse
//
//  Created by mkaya on 26/07/2017.
//  Copyright © 2017 mkaya. All rights reserved.
//

#include "stringFuncs.h"
char *getString(char *string,int baslangic, int bitis){
    char *parca = (char*)malloc(bitis+1-baslangic*sizeof(char));
    int i;
    int a = 0;
    for(i = baslangic-1; i < bitis; i++){
        parca[a] = string[i];
        a++;
    }
    parca[a] = '\0';
    return parca;
}
double getDouble(char *string,int baslangic, int bitis){
    char parca[bitis-baslangic+1];
    int i;
    int a = 0;
    for(i = baslangic-1; i < bitis; i++){
        parca[a] = string[i];
        a++;
    }
    parca[a] = '\0';
    return atof(parca);
}
int getInt(char *string,int baslangic, int bitis){
    char parca[bitis-baslangic+1];
    int i;
    int a = 0;
    for(i = baslangic-1; i < bitis; i++){
        parca[a] = string[i];
        a++;
    }
    parca[a] = '\0';
    return atoi(parca);
}
char getChar(char *string,int sira){
    return string[sira-1];
}
