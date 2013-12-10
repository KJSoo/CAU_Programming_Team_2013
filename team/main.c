//
//  main.c
//  inging
//
//  Created by inging on 13. 11. 25..
//  Copyright (c) 2013년 inging. All rights reserved.
//

#include <stdio.h>
#include "BaseFunction.h"
#include "MenuStruct.h"
#include "ChainManage.h"
#include "UserInformation.h"
int showMainMenu();
int selectMenu();
void manageMenu();
void manageChain();
void manageUser();

int main(int argc, const char * argv[])
{
    init();
    while(showMainMenu());
}
int showMainMenu(){
    printf("1.Menu management 2.Chain management 3.User management: ");
    return selectMenu();
}
int selectMenu(){
    int select=0;
    scanf("%d",&select);
    switch (select) {
        case 1:
            manageMenu();
            break;
        case 2:
            manageChain();
            break;
        case 3:
            manageUser();
            refreshUserInformation();
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
            manageMenu();
            break;
        default:
            break;
    }
}
void manageChain(){
    int select;
    refreshChain();
    printAllChainList();
    printAndScan("1.chain add 2.chain permission edit 3. chain record : ", &select);
    switch (select) {
        case 1:
        {
            char chainName[_NAME_MAX_]={0};
            printf("cahin name : ");
            scanf("%s",chainName);
            changeBig(chainName);
            if(getCmpChain(chainName)) printf("Already in the %s\n",chainName);
            else {
                createChainStruct(chainName, 2);
                printf("Created\n");
                clearBuffer();
                pause();
                writeAllChainList();
                manageChain();
            }
        }
            break;
        case 2:
        {
            int index = 0;
            int state = 0;
            printAndScan("Index : ", &index);
            printAndScan("State (1.요청중 2.영업중 3.거절됨) : ", &state);
            setPermission(index, state);
            manageChain();
        }
            break;
        case 3:{
            
        }
            break;
        default:
            break;
    }
}
void manageUser(){
    int select;
    printAndScan("1.User Add 2.User Delete 3.User List 4.Find User : ",&select);
    switch (select) {
        case 1:
            createNewUser();
            break;
        case 3:
            printAllUser();
            break;
        case 4:
        {
            int birthDay=0;
            char number[10]={0};
            printf("phone number (not birthday .): ");
            scanf("%s",number);
            if(number[0] == '.') number[0] = '\0';
            printf("birth day (not birthday 0): ");
            scanf("%d",&birthDay);
            findUser(number, birthDay);
        }
        default:
            break;
    }
    if(select != 0)manageUser();
}