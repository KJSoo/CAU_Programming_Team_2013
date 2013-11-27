//
//  main.c
//  inging
//
//  Created by inging on 13. 11. 25..
//  Copyright (c) 2013년 inging. All rights reserved.
//

#ifndef Test_BaseFunction_h
#define Test_BaseFunction_h
#include <stdio.h>

#define _DEFAULT_MENU_FILE_ "menu.txt"
#define _DEFAULT_CHAIN_FILE_ "chain.txt"
#define _NAME_MAX_ 50

int getLength(char *string);
void removeSpace(char *string);
void clearBuffer();
void setStringName(char *setString,char *name);
#endif
