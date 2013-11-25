//
//  main.c
//  Test
//
//  Created by bluegg on 13. 11. 25..
//  Copyright (c) 2013년 bluegg. All rights reserved.
//

#include <stdio.h>
#include "MenuStruct.h"

#define _DEFAULT_MENU_FILE_ "menu.txt"

int showMainMenu();
int selectMenu();
void manageMenu();

Menu *menu = NULL;

int main(int argc, const char * argv[])
{
    menu = initMenuStrut(_DEFAULT_MENU_FILE_);
    while(showMainMenu());
}

int showMainMenu(){
    printf("1.메뉴 관리 2.xxx : ");
    return selectMenu();
}
int selectMenu(){
    int select=0;
    scanf("%d",&select);
    switch (select) {
        case 1:
            manageMenu();
            break;
        case 0:
            printf("exit.");
            break;
        default:
            select = -1;
            break;
    }
    return select;
}
void manageMenu(){
    int select;
    printAllMenuList(menu);
    printf("1.메뉴 추가 2.메뉴 삭제 3.되돌아가기 : ");
    scanf("%d",&select);
    switch (select) {
        case 1:
        {
            char name[_NAME_MAX_];
            int price;
            clearBuffer();
            printf("메뉴 이름 : ");
            scanf("%[^\n]",name);
            printf("가격 : ");
            scanf("%d",&price);
            menu = createMenuStruct(getTailNode(menu), name, price);
            manageMenu();
        }
            break;
        case 2:
        {
            int select;
            printf("삭제할 메뉴 : ");
            scanf("%d",&select);
            menu = deleteMenu(menu,select);
            manageMenu();
        }
            break;
        default:
            break;
    }
}