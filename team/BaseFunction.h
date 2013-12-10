//
//  main.c
//  inging
//
//  Created by inging on 13. 11. 25..
//  Copyright (c) 2013³â inging. All rights reserved.
//

#ifndef Test_BaseFunction_h
#define Test_BaseFunction_h

#include <stdio.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>

#define _DEFAULT_MENU_FILE_ "menu.txt"
#define _DEFAULT_CHAIN_FILE_ "chain.txt"
#define _DEFAULT_USER_FILE_ "user.txt"
#define _NAME_MAX_ 50

#define OS 1 // 1 = window 2 = os x

int getLength(char *string);
void removeSpace(char *string);
void clearBuffer();
void setStringName(char *setString,char *name);
void changeBig(char *string);
int cmpString(char *string1, char *string2);
void init();
void clear();
void pause();
void printAndScan(char *string,int *value);
int isContainString(char *firstString, char*secondString);
#endif
