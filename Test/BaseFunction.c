//
//  BaseFunction.c
//  Test
//
//  Created by bluegg on 13. 11. 25..
//  Copyright (c) 2013년 bluegg. All rights reserved.
//

#include "BaseFunction.h"

int getLength(char *string){
    int i = 0;
    while(string[i] != '\0')
        i++;
    return i;
}
void removeSpace(char *string){
    int length = getLength(string);
    while (length > 0) {
        if(string[length-1] == ' ') length--;
        else break;
    }
    string[length] = '\0';
}
void clearBuffer(){
    while(getchar() != '\n');
}