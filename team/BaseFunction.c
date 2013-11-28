//
//  main.c
//  inging
//
//  Created by inging on 13. 11. 25..
//  Copyright (c) 2013년 inging. All rights reserved.
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
void setStringName(char *setString,char *name){
    if(name == NULL) name = NULL;
    else{
        int i;
        int length = getLength(name);
        for(i = 0 ; i < length && i < _NAME_MAX_-1 ; i++){
            setString[i] = name[i];
        }
        setString[i] = '\0';
    }
}
void changeBig(char *string){
	int i;
	for(i = 0 ; i < getLength(string) ; i++){
		if(string[i] >= 'a' && string[i] <= 'z') string[i] -= 32;
	}
}
int cmpString(char *string1, char *string2){
	return 0;
}