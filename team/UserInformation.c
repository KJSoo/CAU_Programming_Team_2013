//
//  UserInformation.c
//  Test
//
//  Created by JiSoo Kim on 13. 12. 8..
//  Copyright (c) 2013년 bluegg. All rights reserved.
//

#include "UserInformation.h"

UserInformation *_user = NULL;

void initUserInformation(const char* fileName){
    FILE *pFile = fopen(_DEFAULT_USER_FILE_,"r");
    char name[20];
    char phoneNumber[15];
    int point,dirthDay;
    if(pFile == NULL) return;
    while(fscanf(pFile, "%[^ ] %[^ ] %d %d",name,phoneNumber,&dirthDay,&point) != -1){
        fgetc(pFile);
        _user = createUserStruct(name, phoneNumber,dirthDay,point);
    }
}
void refreshUserInformation(){
    _user = getUserHeadNode();
    if(_user == NULL);
    else
        while (_user->next != NULL) {
            _user = _user->next;
            free(_user->prev);
        }
    if(_user != NULL) free(_user);
    _user = NULL;
    initUserInformation(_DEFAULT_USER_FILE_);
}
UserInformation* createUserStruct(char *name, char *phoneNumber,int dirthDay,int point){
    UserInformation *user = (UserInformation*)malloc(sizeof(UserInformation));
    setStringName(user->name, name);
    setStringName(user->phoneNumber, phoneNumber);
    user->point = point;
    user->birthDay = dirthDay;
    connectUserNode(getUserTailNode(), user);
    if(user->prev == NULL) user->index = 1;
    else user->index = user->prev->index + 1;
    return user;
}
void connectUserNode(UserInformation* prevNode, UserInformation* presentNode){
    if(prevNode != NULL){
        prevNode -> next = presentNode;
        presentNode -> prev = prevNode;
    }
    else{
        presentNode -> prev = NULL;
        _user = presentNode;
    }
    presentNode -> next = NULL;
}
UserInformation* getUserHeadNode(){
    if(_user == NULL) return NULL;
    else{
        while(_user->prev != NULL){
            _user = _user -> prev;
        }
        return _user;
    }
}

UserInformation* getUserTailNode(){
    if(_user == NULL) return NULL;
    else{
        while(_user->next != NULL){
            _user = _user -> next;
        }
        return _user;
    }
}
UserInformation *getUserByIndex(int index){
    if(_user == NULL) return NULL;
    else{
        UserInformation *head = getUserHeadNode(); // head 부터 tail 까지 순차적 순회를 합니다.
        while(head != NULL){
            if(head -> index == index) return head;
            else head = head -> next;
        }
        return head; // index 와 일치하는 값이 없을경우 NULL 을 리턴합니다.
    }
}
void printAllUser(){
    UserInformation *temp = getUserHeadNode();
    clear();
    if( temp == NULL) printf("메뉴가 없습니다.\n");
    else{
        while (temp != NULL) {
            printf("%d %s %s %d %d\n",temp -> index, temp -> name, temp -> phoneNumber,temp->birthDay,temp->point);
            temp = temp->next;
        }
    }
}
int editUserPoint(char variation,int index, int point){
    UserInformation *temp = getUserByIndex(index);
    if(temp == NULL) return 0;
    if(variation == '+'){
        temp -> point += point;
        writeAllUser();
        return 1;
    }else if(variation == '-'){
        if(temp -> point - point >= 0){
            temp->point -= point;
            writeAllUser();
            return 1;
        }
        else return 0;
        
    }else return 0;
}
void findUser(char *number,int birthDay){
    UserInformation *temp = getUserHeadNode();
    while (temp != NULL) {
        if(birthDay != 0 && temp->birthDay == birthDay && isContainString(temp->phoneNumber, number)){
            printf("%d %s %s %d %d\n",temp -> index, temp -> name, temp -> phoneNumber,temp->birthDay,temp->point);
        }else if(birthDay == 0 && isContainString(temp->phoneNumber, number)){
            printf("%d %s %s %d %d\n",temp -> index, temp -> name, temp -> phoneNumber,temp->birthDay,temp->point);
        }else if(number == NULL && temp->birthDay == birthDay)
            printf("%d %s %s %d %d\n",temp -> index, temp -> name, temp -> phoneNumber,temp->birthDay,temp->point);
        temp = temp->next;
    }
}
void writeAllUser(){
    FILE *pFile = fopen(_DEFAULT_USER_FILE_, "w");
    UserInformation *temp = getUserHeadNode();
    while (temp != NULL) {
        fprintf(pFile, "%s %s %d %d\n",temp->name,temp->phoneNumber,temp->birthDay,temp->point);
        temp = temp->next;
    }
}