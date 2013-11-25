//
//  MenuStruct.h
//  Test
//
//  Created by bluegg on 13. 11. 25..
//  Copyright (c) 2013년 bluegg. All rights reserved.
//

#ifndef Test_MenuStruct_h
#define Test_MenuStruct_h

#define _NAME_MAX_ 50

#include <stdlib.h>
#include <stdio.h>
#include "BaseFunction.h"

struct MenuStruct{
    int index;
    char menuName[_NAME_MAX_];
    int price;
    struct MenuStruct *past;
    struct MenuStruct *next;
}typedef Menu;

Menu* createMenuStruct(Menu* pastNode, char *name, int price); /* pastNode, index, name, price 를 받습니다.
                                                                            pastNode 가 없을 경우 NULL 를 줍니다.
                                                                            index 에 0을 입력하면 auto 로 index가 생깁니다.(항상 0을 넘겨도 무관)
                                                                            name 이 없을 경우 NULL 를 줍니다.(비정상적인 상황)
                                                                            price 에 int 값을 줍니다. 없을 경우 0을 줍니다.(비정상적인 상황) */
void setIndex(Menu *menu);
void setMenuName(Menu *menu,char *name);
void setMenuPrice(Menu *menu,int price);
void setMenuNameAndPrice(Menu *menu, char *name, int price);
void setMenuAllData(Menu *menu, char *name, int price);
void connectNode(Menu* pastNode, Menu* presentNode);//이전 노드와 현재 노드를 연결합니다.

Menu* getHeadNode(Menu *menu);                  //아무 menu 나 넘겨주면 head node 를 돌려줍니다.
Menu* getTailNode(Menu *menu);                  //아무 menu 나 넘겨주면 tail node 를 돌려줍니다.
Menu* getIndexOfNode(Menu *menu, int index);    //아무 menu 와 index 를 넘겨주면 해당 index 의 Node 를 넘겨줍니다. index 와 일치하는 노드가 없으면 NULL 을 리턴합니다.

Menu* initMenuStrut(const char *fileName);
void writeAllMenuList(const char *fileName, Menu *menu);
void writeOneNode(const char *fileName, Menu *menu);
#endif
