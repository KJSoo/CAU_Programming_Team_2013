//
//  main.c
//  inging
//
//  Created by inging on 13. 11. 25..
//  Copyright (c) 2013년 inging. All rights reserved.
//

#include "BaseFunction.h"
#include "ChainManage.h"
#include "MenuStruct.h"

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
    int firstStringLength = getLength(string1);
    int secondStringLength = getLength(string2);
    if(firstStringLength == secondStringLength){
        int i = 0;
        for(; i < firstStringLength ; i++){
            if(string1[i] != string2[i]) return 0;
        }
        return 1;
    }
	return 0;
}
void init(){
    initMenuStrut(_DEFAULT_MENU_FILE_);
    initChainStrut(_DEFAULT_CHAIN_FILE_);
}
void clear(){
    if(OS == 1){
        system("cls");
    }
    else if(OS == 2){
        system("clear");
    }
}
void pause(){
    if(OS == 1){
        system("pause");
    }else if(OS == 2){
        printf("Press any enter to continue...");
        getchar();
    }
}
void printAndScan(char *string,int *value){
    printf("%s",string);
    scanf("%d",value);
}