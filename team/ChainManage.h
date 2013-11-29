//
//  main.c
//  inging
//
//  Created by inging on 13. 11. 25..
//  Copyright (c) 2013년 inging. All rights reserved.
//

#ifndef Test_ChainManage_h
#define Test_ChainManage_h

#include "BaseFunction.h"

struct chain{
    char chainName[_NAME_MAX_];
    int state;
    int index;
    
	struct chain *next;
	struct chain *past;
}typedef Chain;

void initChainStrut(const char *fileName);
Chain* createChainStruct(char *name, int state);
Chain* getChainHeadNode();
Chain* getChainTailNode();
Chain* getIndexOfChainNode(int index);
void connectChainNode(Chain* pastNode, Chain* presentNode);
void setPermission(int index, int status);
int getPermission(char *string);
int getCmpChain(char *string);
void printAllChainList();
void requestChain(char *string);
void writeAllChainList();
void refreshChain();
#endif
