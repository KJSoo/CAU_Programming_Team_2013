//
//  MenuStruct.c
//  Test
//
//  Created by bluegg on 13. 11. 25..
//  Copyright (c) 2013년 bluegg. All rights reserved.
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
void updateIndex(Menu *menu){
    int i = 1;
    menu = getHeadNode(menu);
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
        printf("목록이 없습니다.\n");
        return;
    }
    if(getIndexOfNode(index) == NULL){
        printf("없는 메뉴 입니다.\n");
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
        updateIndex(head);
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
    if( temp == NULL) printf("메뉴가 없습니다.\n");
    else{
        printf("Index\t MenuName\t Price\n");
        while (temp != NULL) {
            printf("%d\t%s\t\t%d\n",temp -> index, temp -> menuName, temp -> price);
            temp = temp->next;
        }
    }
}
void writeAllMenuList(const char *fileName){
    Menu *head = getHeadNode();
    FILE *pFile = fopen(fileName, "w");
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
void writeChainMenuList(const char*fileName){
    head = getHeadNode();
    FILE *pFile = fopen(fileName, "w");
    while (head != NULL) {
        fprintf(pFile, "%s %d %d\n",head->menuName,head->price,head->sellCount);
        head = head->next;
    }
    fclose(pFile);
}
void addSellCountByIndex(int index, int count){
    Menu *temp = getIndexOfNode(index);
    if(temp == NULL) return;
    else temp -> sellCount += count;
}