//
//  MenuStruct.c
//  Test
//
//  Created by bluegg on 13. 11. 25..
//  Copyright (c) 2013년 bluegg. All rights reserved.
//

#include "MenuStruct.h"

Menu *head = NULL;

Menu* initMenuStrut(const char *fileName){
    FILE *pFile = fopen(fileName, "r");
    Menu *temp=NULL;
    char tempName[_NAME_MAX_*2] = {0};
    int tempPrice;
    if(pFile == NULL) return NULL;
    while(fscanf(pFile, "%[^0-9] %d",tempName,&tempPrice) != -1){
        fgetc(pFile);
        temp = createMenuStruct(temp, tempName, tempPrice);
        removeSpace(temp->menuName);
    }
    fclose(pFile);
    return getHeadNode(temp);
}
Menu* createMenuStruct(Menu* pastNode, char *name, int price){
    Menu *menu = (Menu*)malloc(sizeof(Menu));
    menu -> sellCount = 0;
    connectNode(pastNode, menu);
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
    }
    presentNode -> next = NULL;
}
Menu* deleteMenu(Menu* menu, int index){
    Menu *temp;
    if(menu == NULL) {
        printf("목록이 없습니다.");
        return NULL;
    }
    if(getIndexOfNode(menu, index) == NULL){
        printf("없는 메뉴 입니다.");
        return menu;
    }
    temp = getIndexOfNode(menu, index);
    
    if(temp -> next != NULL && temp -> past != NULL){
        temp -> past -> next = temp -> next;
        temp -> next -> past = temp -> past;
        menu = temp -> past;
        free(temp);
    }else if(temp -> next != NULL && temp -> past == NULL){
        temp -> next -> past = NULL;
        menu = temp -> next;
        free(temp);
    }else if(temp -> next == NULL && temp -> past != NULL){
        temp -> past -> next = NULL;
        menu = temp -> past;
        free(temp);
    }else {
        free(temp);
        menu = NULL;
        temp = NULL;
    }
    if(menu != NULL) {
        updateIndex(menu);
        return getHeadNode(menu);
    }else return NULL;
}
Menu* getHeadNode(Menu *menu){
    if(menu == NULL) return NULL;
    else{
        Menu *temp = menu;
        while(temp->past != NULL){
            temp = temp -> past;
        }
        return temp;
    }
}
Menu* getTailNode(Menu *menu){
    if(menu == NULL) return NULL;
    else{
        Menu *temp = menu;
        while(temp->next != NULL){
            temp = temp -> next;
        }
        return temp;
    }
}
Menu* getIndexOfNode(Menu *menu, int index){
    if(menu == NULL) return NULL;
    else{
        Menu *temp = getHeadNode(menu); // head 부터 tail 까지 순차적 순회를 합니다.
        while(temp != NULL){
            if(temp -> index == index) return temp;
            else temp = temp -> next;
        }
        return temp; // index 와 일치하는 값이 없을경우 NULL 을 리턴합니다.
    }
}
void printAllMenuList(Menu *menu){
    Menu *temp = getHeadNode(menu);
    if( temp == NULL) printf("메뉴가 없습니다.\n");
    else{
        printf("Index\t MenuName\t Price\n");
        while (temp != NULL) {
            printf("%d\t%s\t\t%d\n",temp -> index, temp -> menuName, temp -> price);
            temp = temp->next;
        }
    }
}
void writeAllMenuList(const char *fileName, Menu *menu){
    Menu *head = getHeadNode(menu);
    FILE *pFile = fopen(fileName, "w");
    while (head != NULL) {
        fprintf(pFile, "%s %d\n",head->menuName,head->price);
        head = head->next;
    }
    fclose(pFile);
}
void writeOneNode(const char *fileName, Menu *menu){
    FILE *pFile = fopen(fileName, "a");
    fprintf(pFile, "%s %d\n",menu->menuName,menu->price);
    fclose(pFile);
}
void writeChainMenuList(const char*fileName, Menu*menu){
    Menu *head = getHeadNode(menu);
    FILE *pFile = fopen(fileName, "w");
    while (head != NULL) {
        fprintf(pFile, "%s %d %d\n",head->menuName,head->price,head->sellCount);
        head = head->next;
    }
    fclose(pFile);
}
void addSellCountByIndex(Menu *menu, int index, int count){
    Menu *temp = getIndexOfNode(menu, index);
    if(temp == NULL) return;
    else temp -> sellCount += count;
}