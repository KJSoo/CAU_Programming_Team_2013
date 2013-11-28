//
//  main.c
//  inging
//
//  Created by inging on 13. 11. 25..
//  Copyright (c) 2013년 inging. All rights reserved.
//

#include <stdio.h>
#include "MenuStruct.h"

int showMainMenu();
int selectMenu();
void manageMenu();


int main(int argc, const char * argv[])
{
    initMenuStrut(_DEFAULT_MENU_FILE_);
    while(showMainMenu());
}

int showMainMenu(){
    printf("1.menu management 2.xxx : ");
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
    printAllMenuList();
    printf("\n1.menu add 2.menu delete 3.menu save 4. exit : ");
    scanf("%d",&select);
    switch (select) {
        case 1:
        {
            char name[_NAME_MAX_];
            int price;
            clearBuffer();
            printf("manu name : ");
            scanf("%[^\n]",name);
            printf("price : ");
            scanf("%d",&price);
            createMenuStruct(name, price);
            manageMenu();
        }
            break;
        case 2:
        {
            int select;
            printf("delete menu number : ");
            scanf("%d",&select);
            deleteMenu(select);
            manageMenu();
        }
            break;
        case 3:
            writeAllMenuList(_DEFAULT_MENU_FILE_);
            break;
        default:
            break;
    }
}