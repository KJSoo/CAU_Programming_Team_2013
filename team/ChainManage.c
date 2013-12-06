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
	int state;
    if(pFile == NULL) return;
    while(fscanf(pFile, "%[^0-9] %d",tempName,&state) != -1){
        fgetc(pFile);
		changeBig(tempName);
        removeSpace(tempName);
        if(getCmpChain(tempName)) continue;
        chain = createChainStruct(tempName, state);
    }
    fclose(pFile);
    chain = getChainHeadNode();
}
Chain* createChainStruct(char *name, int state){
    Chain *chain = (Chain*)malloc(sizeof(Chain));
	setStringName(chain->chainName,name);
	chain -> state = state;
	connectChainNode(getChainTailNode(),chain);
    if(chain -> past == NULL) chain->index = 1;
    else chain -> index = chain -> past -> index +1;
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
Chain* getIndexOfChainNode(int index){
    if(chain == NULL) return NULL;
    else{
        Chain *temp = getChainHeadNode(); // head 부터 tail 까지 순차적 순회를 합니다.
        while(temp != NULL){
            if(temp -> index == index) return temp;
            else temp = temp -> next;
        }
        return temp; // index 와 일치하는 값이 없을경우 NULL 을 리턴합니다.
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
void setPermission(int index, int state){
    Chain *temp = getIndexOfChainNode(index);
    if(temp == NULL) printf("not chain");
    else {
        temp -> state = state;
    }
}
int getPermission(char *string){
	chain = getChainHeadNode();
	if(chain == NULL) return 0;
	while(1){
        if(cmpString(string, chain->chainName)){
            return chain->state;
        }
		if(chain -> next == NULL) break;
		chain = chain -> next;
        writeAllChainList();
	}
    return 0;
}
int getCmpChain(char *string){
    Chain *temp = getChainHeadNode();
    if(temp == NULL) return 0;
    while(1){
        if(cmpString(string, temp->chainName)) return 1;
        if(temp -> next == NULL) break;
        temp = temp->next;
    }
    return 0;
}
void printAllChainList(){
    Chain *temp = getChainHeadNode();
    clear();
    if( temp == NULL) printf("net Chain\n");
    else{
        printf("│───────│────────────────────────────────│─────────│\n");
        printf("│ Index │ ChainName\t\t\t │  State  │\n");
        printf("│───────┼────────────────────────────────┼─────────┼\n");
        while (temp != NULL) {
            printf("%4d  %-31s",temp -> index, temp -> chainName);
            if(temp->state == 1) printf("  요청중  │\n");
            else if(temp -> state == 2) printf("  영업중  │\n");
            else if(temp -> state == 3) printf("  거절됨  │\n");
            else printf(" 없음 \n");
            temp = temp->next;
        }
        printf("│───────│────────────────────────────────│─────────│\n");
    }
}
void requestChain(char *string){
    if(getCmpChain(string)) return;
    createChainStruct(string, 1);
    writeAllChainList();
}
void writeAllChainList(){
    FILE *pFile = fopen(_DEFAULT_CHAIN_FILE_, "w");
    Chain *temp = getChainHeadNode();
    while (temp != NULL) {
        fprintf(pFile, "%s %d\n",temp->chainName,temp->state);
        if(temp -> next == NULL) break;
        temp = temp->next;
    }
    fclose(pFile);
}
void refreshChain(){
    initChainStrut(_DEFAULT_CHAIN_FILE_);
}