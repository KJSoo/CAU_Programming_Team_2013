//
//  MenuStruct.c
//  Test
//
//  Created by bluegg on 13. 11. 25..
//  Copyright (c) 2013년 bluegg. All rights reserved.
//

#include "MenuStruct.h"

Menu* createMenuStruct(Menu* pastNode,int index, char *name, int price){
    Menu *menu = (Menu*)malloc(sizeof(Menu));
    connectNode(pastNode, menu);
    setMenuAllData(menu, index, name, price);
    return menu;
}
void setIndex(Menu *menu, int index){
    if(index == 0){
        if(menu -> past != NULL)
            menu -> index = menu -> past -> index+1;
        else
            menu -> index = 1;
    }
    else
        menu -> index = index;
}
void setMenuName(Menu *menu,char *name){
    if(name == NULL) name = NULL;
    else{
        int i;
        int length = getLength(name);
        for(i = 0 ; i < length && i < _NAME_MAX_-1 ; i++){
            menu -> menuName[i] = name[i];
        }
        menu -> menuName[i] = '\0';
    }
}
void setMenuPrice(Menu *menu,int price){
    if(price == 0)
        price = -1;
    else
        menu -> price = price;
}
void setMenuNameAndPrice(Menu *menu, char *name, int price){
    setMenuName(menu, name);
    setMenuPrice(menu,price);
}
void setMenuAllData(Menu *menu,int index, char *name, int price){
    setIndex(menu, index);
    setMenuNameAndPrice(menu, name, price);
}
void connectNode(Menu* pastNode, Menu* presentNode){
    if(pastNode != NULL){
        pastNode -> next = presentNode;
        presentNode -> past = pastNode;
    }
    else{
        presentNode -> past = NULL;
        presentNode -> next = NULL;
    }
}
Menu* getHeadNode(Menu *menu){
    if(menu == NULL) return NULL;
    else{
        Menu *temp = menu;
        if(temp -> past == NULL) return temp;
        else temp = temp -> past;
        return temp;
    }
}
Menu* getTailNode(Menu *menu){
    if(menu == NULL) return NULL;
    else{
        Menu *temp = menu;
        if(temp -> next == NULL) return temp;
        else temp = temp -> next;
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