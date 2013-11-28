//
//  main.c
//  inging
//
//  Created by inging on 13. 11. 25..
//  Copyright (c) 2013년 inging. All rights reserved.
//

#include "ChainManage.h"

Chain *chain = NULL;

void initChainStrut(const char *fileName){
    FILE *pFile = fopen(fileName, "r");
    char tempName[_NAME_MAX_*2] = {0};
	int status;
    if(pFile == NULL) return;
    while(fscanf(pFile, "%[^0-9] %d",tempName,&status) != -1){
        fgetc(pFile);
		changeBig(tempName);
        chain = createChainStruct(tempName, status);
        removeSpace(chain->chainName);
    }
    fclose(pFile);
    chain = getChainHeadNode();
}
Chain* createChainStruct(char *name, int status){
    Chain *chain = (Chain*)malloc(sizeof(Chain));
	setStringName(chain->chainName,name);
	chain -> state = status;
	connectChainNode(getChainTailNode(),chain);
    return chain;
}
Chain* getChainHeadNode(){
    if(chain == NULL) return NULL;
    else{
        while(chain->past != NULL){
            chain = chain -> past;
        }
        return chain;
    }
}
Chain* getChainTailNode(){
    if(chain == NULL) return NULL;
    else{
        while(chain->next != NULL){
            chain = chain -> next;
        }
        return chain;
    }
}
void connectChainNode(Chain* pastNode, Chain* presentNode){
    if(pastNode != NULL){
        pastNode -> next = presentNode;
        presentNode -> past = pastNode;
    }
    else{
        presentNode -> past = NULL;
        chain = presentNode;
    }
    presentNode -> next = NULL;
}
int getChainStatus(char *string){
	chain = getChainHeadNode();
	if(chain == NULL) return 0;
	while(1){

		if(chain -> next == NULL) break;
		chain = chain -> next;
	}
}