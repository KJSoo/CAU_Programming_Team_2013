//
//  main.c
//  inging
//
//  Created by inging on 13. 11. 25..
//  Copyright (c) 2013년 inging. All rights reserved.
//

#include "MenuStruct.h"

Menu *head = NULL;

void initMenuStrut(const char *fileName){
    FILE *pFile = fopen(fileName, "r");
    char tempName[_NAME_MAX_*2] = {0};
    int tempPrice;
    if(pFile == NULL) return;
    while(fscanf(pFile, "%[^0-9] %d",tempName,&tempPrice) != -1){
        fgetc(pFile);
        head = createMenuStruct(tempName, tempPrice);
        removeSpace(head->menuName);
    }
    fclose(pFile);
    head = getHeadNode();
}
Menu* createMenuStruct(char *name, int price){
    Menu *menu = (Menu*)malloc(sizeof(Menu));
    menu -> sellCount = 0;
	menu -> allSellCount = 0;
    connectNode(getTailNode(), menu);
    setMenuAllData(menu, name, price);
    return menu;
}
void setIndex(Menu *menu){
    if(menu -> past != NULL)
        menu -> index = menu -> past -> index+1;
    else
        menu -> index = 1;
}
void setMenuPrice(Menu *menu,int price){
    if(price == 0)
        price = -1;
    else
        menu -> price = price;
}
void setMenuNameAndPrice(Menu *menu, char *name, int price){
    setStringName(menu->menuName, name);
    setMenuPrice(menu,price);
}
void setMenuAllData(Menu *menu, char *name, int price){
    setIndex(menu);
    setMenuNameAndPrice(menu, name, price);
}
void updateIndex(){
    int i = 1;
    Menu *menu = getHeadNode();
    while(menu != NULL){
        menu -> index = i++;
        menu = menu->next;
    }
}

void connectNode(Menu* pastNode, Menu* presentNode){
    if(pastNode != NULL){
        pastNode -> next = presentNode;
        presentNode -> past = pastNode;
    }
    else{
        presentNode -> past = NULL;
        head = presentNode;
    }
    presentNode -> next = NULL;
}
void deleteMenu(int index){
    Menu *temp;
    if(head == NULL) {
        printf("not exist menu list\n");
        return;
    }
    if(getIndexOfNode(index) == NULL){
        printf("no menu.\n");
        return;
    }
    temp = getIndexOfNode(index);
    
    if(temp -> next != NULL && temp -> past != NULL){
        temp -> past -> next = temp -> next;
        temp -> next -> past = temp -> past;
        head = temp -> past;
        free(temp);
    }else if(temp -> next != NULL && temp -> past == NULL){
        temp -> next -> past = NULL;
        head = temp -> next;
        free(temp);
    }else if(temp -> next == NULL && temp -> past != NULL){
        temp -> past -> next = NULL;
        head = temp -> past;
        free(temp);
    }else {
        free(temp);
        head = NULL;
        temp = NULL;
    }
    if(head != NULL) {
        updateIndex();
        return;
    }else return;
}

Menu* getHeadNode(){
    if(head == NULL) return NULL;
    else{
        while(head->past != NULL){
            head = head -> past;
        }
        return head;
    }
}

Menu* getTailNode(){
    if(head == NULL) return NULL;
    else{
        while(head->next != NULL){
            head = head -> next;
        }
        return head;
    }
}

Menu* getIndexOfNode(int index){
    if(head == NULL) return NULL;
    else{
        Menu *head = getHeadNode(); // head 부터 tail 까지 순차적 순회를 합니다.
        while(head != NULL){
            if(head -> index == index) return head;
            else head = head -> next;
        }
        return head; // index 와 일치하는 값이 없을경우 NULL 을 리턴합니다.
    }
}

void printAllMenuList(){
    Menu *temp = getHeadNode();
    clear();
    if( temp == NULL) printf("메뉴가 없습니다.\n");
    else{
        printf("│───────│────────────────────────────────│───────│\n");
        printf("│ Index │ MenuName\t\t\t │ Price │\n");
        printf("│───────┼────────────────────────────────┼───────┼\n");
        while (temp != NULL) {
            printf("│%4d   │ %-31s│ %5d │\n",temp -> index, temp -> menuName, temp -> price);
            temp = temp->next;
        }
        printf("│───────│────────────────────────────────│───────│\n");
    }
}

void writeAllMenuList(const char *fileName){
	FILE *pFile = fopen(fileName, "w");
    Menu *head = getHeadNode();
    while (head != NULL) {
        fprintf(pFile, "%s %d\n",head->menuName,head->price);
        head = head->next;
    }
    fclose(pFile);
}

void writeOneNode(const char *fileName, int index){
    FILE *pFile = fopen(fileName, "a");
    Menu *menu = getIndexOfNode(index);
    if(menu != NULL)
        fprintf(pFile, "%s %d\n",menu->menuName,menu->price);
    fclose(pFile);
}
void addSellCountByIndex(int index, int count){
    Menu *temp = getIndexOfNode(index);
    if(temp == NULL) return;
    else temp -> sellCount += count;
}
int writeChainMenuList(const char*fileName){
	FILE *pFile;
	int amount = 0;
    char temp[50];
    strcpy(temp,fileName);
    strcat(temp,".txt");
    pFile = fopen(temp, "w");
    head = getHeadNode();
    while (head != NULL) {
        fprintf(pFile, "%s %d %d\n",head->menuName,head->price,head->allSellCount);
		amount += (head->price * head->sellCount);
		head -> allSellCount += head -> sellCount;
		head -> sellCount = 0;
		if(head -> next == NULL) break;
        head = head->next;
    }
    fclose(pFile);
	return amount;
}