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

	struct chain *next;
	struct chain *past;
}typedef Chain;

void initChainStrut(const char *fileName);
Chain* createChainStruct(char *name, int status);
Chain* getChainHeadNode();
Chain* getChainTailNode();
void connectChainNode(Chain* pastNode, Chain* presentNode);
int getChainStatus(char *string);
#endif
