//
//  main.c
//  inging
//
//  Created by inging on 13. 11. 25..
//  Copyright (c) 2013�� inging. All rights reserved.
//

#ifndef Test_MenuStruct_h
#define Test_MenuStruct_h

#include "BaseFunction.h"

struct MenuStruct{
    int index;
    char menuName[_NAME_MAX_];
    int price;
    int sellCount;
	int allSellCount;
    struct MenuStruct *past;
    struct MenuStruct *next;
}typedef Menu;

void initMenuStrut(const char *fileName);
Menu* createMenuStruct(char *name, int price);
void setIndex(Menu *menu);
void setMenuPrice(Menu *menu,int price);
void setMenuNameAndPrice(Menu *menu, char *name, int price);
void setMenuAllData(Menu *menu, char *name, int price);
void updateIndex();

void connectNode(Menu* pastNode, Menu* presentNode);
void deleteMenu(int index);
void printOrder(const char *fileName);

Menu* getHeadNode();
Menu* getTailNode();
Menu* getIndexOfNode(int index); // you can get node of index, if not exist return null. you must check return type.

void printAllMenuList();  // print All menu list.

void writeAllMenuList(const char *fileName);
void writeOneNode(const char *fileName, int index);

void addSellCountByIndex(int index, int count); // if you give menu index number and sell count, struct menu add sellcount.
int getSellMoney();
int writeChainMenuList(const char*fileName);
void writeUserBuy(char *store, char *name,int point);
#endif
