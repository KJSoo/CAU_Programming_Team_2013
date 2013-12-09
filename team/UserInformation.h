//
//  UserInformation.h
//  Test
//
//  Created by JiSoo Kim on 13. 12. 8..
//  Copyright (c) 2013년 bluegg. All rights reserved.
//

#ifndef Test_UserInformation_h
#define Test_UserInformation_h
#include "BaseFunction.h"

struct _UserInformation{
    int index;
    int point;
    int birthDay;
    char phoneNumber[15];
    char name[20];
    
    struct _UserInformation *next;
    struct _UserInformation *prev;
}typedef UserInformation;
void initUserInformation(const char* fileName);
void refreshUserInformation();
UserInformation* createUserStruct(char *name, char *phoneNumber,int dirthDay,int point);
void connectUserNode(UserInformation* prevNode, UserInformation* presentNode);
UserInformation* getUserHeadNode();
UserInformation* getUserTailNode();
UserInformation *getUserByIndex(int index);
void printAllUser();
int editUserPoint(char variation, int index ,int point);
void findUser(char *number,int birthDay);
void writeAllUser();
#endif
